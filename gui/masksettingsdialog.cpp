#include "gui/masksettingsdialog.h"
#include "ui_masksettingsdialog.h"

#include <QIntValidator>
#include <QBrush>
#include <QColor>
#include <QMenu>
#include <QAction>
#include <QDebug>

MaskSettingsDialog::MaskSettingsDialog(QSharedPointer<Mask> t_mask,
                                       QWidget *parent) :
    QDialog(parent), ui(new Ui::MaskSettingsDialog), m_mask(t_mask)
{
    ui->setupUi(this);

    SetMaskSizeValues();
    SetUpTable();

    ui->maskTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->maskTable, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(SlotShowContextMenu(QPoint)));

    connect(ui->maskTable, SIGNAL(cellChanged(int,int)),
            this, SLOT(SlotCellChanged(int,int)));
}

MaskSettingsDialog::~MaskSettingsDialog()
{
    delete ui;
}

// Set to gui elements size of mask
void MaskSettingsDialog::SetMaskSizeValues()
{
    QIntValidator *rowsValidator = new QIntValidator(ui->rowsLE);
    rowsValidator->setBottom(1);
    rowsValidator->setTop(5000);
    ui->rowsLE->setValidator(rowsValidator);
    ui->rowsLE->setText(QString::number(m_mask->GetRowsNum()));

    QIntValidator *colsValidator = new QIntValidator(ui->colsLE);
    colsValidator->setBottom(1);
    rowsValidator->setTop(5000);
    ui->colsLE->setValidator(colsValidator);
    ui->colsLE->setText(QString::number(m_mask->GetColsNum()));
}

// Set up Table that represent mask
void MaskSettingsDialog::SetUpTable()
{
    ui->maskTable->setRowCount(m_mask->GetRowsNum());
    ui->maskTable->setColumnCount(m_mask->GetColsNum());

    // Set up all cells
    for ( int row = 0; row < ui->maskTable->rowCount(); ++row )
    {
        for ( int col = 0; col < ui->maskTable->columnCount(); ++col )
        {
            QTableWidgetItem *item = ui->maskTable->item(row, col);
            if ( nullptr == item )
            {
                item = new QTableWidgetItem();
                ui->maskTable->setItem(row, col, item);
            }

            SetItemView(item);

            double weight =
                    m_mask->GetPixelWeight(static_cast<unsigned int>(row),
                                           static_cast<unsigned int>(col));

            QString weightStr = QString::number(weight);
            item->setText( weightStr );
        }
    }
}

// Set view of mask item on base of its type
// @input:
// - *t_item - valid pointer to item widget
void MaskSettingsDialog::SetItemView(QTableWidgetItem *t_item)
{
    if ( nullptr == t_item )
    {
        qDebug() << __FUNCTION__ << "Invalid arguments";
        return;
    }

    unsigned int row = static_cast<unsigned int>(t_item->row());
    unsigned int col = static_cast<unsigned int>(t_item->column());

    CellType type = DISABLED;
    if ( m_mask->IsPixelEnabled(row, col) )
    {
        type = ENABLED;
    }

    Qt::ItemFlags cellFlags = t_item->flags();
    switch(type)
    {
        case ENABLED:
            cellFlags |= Qt::ItemIsEditable;
            break;

        case DISABLED:
            cellFlags &= ~Qt::ItemIsEditable;
            break;

        case DEFAULT_LAST:
        default:
        {
            qDebug() << __FUNCTION__ << "Invalid cell type";
        }
    }

    t_item->setFlags(cellFlags);
    t_item->setBackground( GetCellColor(type) );
}

// Get color of cell
// @input:
// - t_type - type of the cell
// @output:
// - QBrush - QBrush object with set up cell color
QBrush MaskSettingsDialog::GetCellColor(const CellType &t_type)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);

    switch(t_type)
    {
        case ENABLED:
            brush.setColor(Qt::white);
            break;

        case DISABLED:
            break;

        case DEFAULT_LAST:
        default:
        {
            qDebug() << __FUNCTION__ << "Invalid cell type";
        }
    }

    return brush;
}

// Slot that will be called on cell change
// @input:
// - t_row - row of changed item
// - t_col - column of changed item
void MaskSettingsDialog::SlotCellChanged(int t_row, int t_col)
{
    QTableWidgetItem *item = ui->maskTable->item(t_row, t_col);
    if ( nullptr == item )
    {
        qDebug() << __FUNCTION__ << "Null item";
        return;
    }

    bool ok = false;
    double weight = item->text().toDouble(&ok);
    if ( false == ok )
    {
        double currentWeight =
                m_mask->GetPixelWeight(static_cast<unsigned int>(t_row),
                                       static_cast<unsigned int>(t_col));

        QString cellStr = QString::number(currentWeight);
        item->setText(cellStr);

        return;
    }

    m_mask->SetPixelWeight(static_cast<unsigned int>(t_row),
                           static_cast<unsigned int>(t_col),
                           weight);
}

// Slot that will show menu
// @input:
// - t_point - point, where user clicked
void MaskSettingsDialog::SlotShowContextMenu(const QPoint &t_point)
{
    QTableWidgetItem *item = ui->maskTable->itemAt(t_point);
    if ( nullptr == item )
    {
        return;
    }

    unsigned int row = static_cast<unsigned int>(item->row());
    unsigned int col = static_cast<unsigned int>(item->column());

    QMenu menu;
    QAction *enabledAction = menu.addAction(tr("Enabled"));
    enabledAction->setCheckable(true);
    enabledAction->setChecked( m_mask->IsPixelEnabled(row, col) );

    if ( enabledAction ==
         menu.exec(ui->maskTable->viewport()->mapToGlobal(t_point)) )
    {
        m_mask->SetPixelActiveStatus(row, col, enabledAction->isChecked());
        SetItemView(item);
    }
}

// Slot that will be called on row number change
void MaskSettingsDialog::on_rowsLE_textEdited()
{
    bool ok = false;
    int rowsNum = ui->rowsLE->text().toInt(&ok);
    if ( false == ok )
    {
        ui->rowsLE->setText( QString::number(m_mask->GetRowsNum()) );
        return;
    }

    m_mask->SetMaskSize(static_cast<unsigned int>(rowsNum),
                        m_mask->GetColsNum());

    SetUpTable();
}

// Slot that will be called on columns number change
void MaskSettingsDialog::on_colsLE_textEdited()
{
    bool ok = false;
    int colsNum = ui->colsLE->text().toInt(&ok);
    if ( false == ok )
    {
        ui->colsLE->setText( QString::number(m_mask->GetColsNum()) );
        return;
    }

    m_mask->SetMaskSize(m_mask->GetRowsNum(),
                        static_cast<unsigned int>(colsNum));

    SetUpTable();
}
