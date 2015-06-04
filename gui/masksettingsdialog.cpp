#include "gui/masksettingsdialog.h"
#include "ui_masksettingsdialog.h"

#include <QIntValidator>
#include <QBrush>
#include <QColor>
#include <QMessageBox>
#include <QDebug>

MaskSettingsDialog::MaskSettingsDialog(QSharedPointer<Mask> t_mask,
                                       QWidget *parent) :
    QDialog(parent), ui(new Ui::MaskSettingsDialog), m_mask(t_mask),
    m_cellMenu(), m_cellEnable(&m_cellMenu), m_cellCentral(&m_cellMenu)
{
    ui->setupUi(this);

    CreateCellMenu();
    SetMaskSizeValues();
    SetUpTable();

    connect(ui->maskTable, SIGNAL(cellChanged(int,int)),
            this, SLOT(SlotCellChanged(int,int)));
}

MaskSettingsDialog::~MaskSettingsDialog()
{
    delete ui;
}

// Create menu widget
void MaskSettingsDialog::CreateCellMenu()
{
    m_cellMenu.setParent(ui->maskTable);

    // This action will enable/disable cell
    m_cellEnable.setText(tr("Enabled"));
    m_cellEnable.setCheckable(true);
    m_cellEnable.setChecked(false);
    connect(&m_cellEnable, SIGNAL(triggered()), this, SLOT(SlotActivateCell()));

    // This action will make any cell central
    m_cellCentral.setText(tr("Central"));
    m_cellCentral.setCheckable(true);
    m_cellCentral.setChecked(false);
    connect(&m_cellCentral, SIGNAL(triggered()), this, SLOT(SlotCenterCell()));

    m_cellMenu.addAction(&m_cellEnable);
    m_cellMenu.addAction(&m_cellCentral);
    m_cellMenu.hide();

    ui->maskTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->maskTable, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(SlotShowContextMenu(const QPoint &)));
}

// Set to gui elements size of mask
void MaskSettingsDialog::SetMaskSizeValues()
{
    QIntValidator *rowsValidator = new QIntValidator(ui->rowsLE);
    rowsValidator->setBottom(1);
    ui->rowsLE->setValidator(rowsValidator);
    ui->rowsLE->setText(QString::number(m_mask->GetRowsNum()));

    QIntValidator *colsValidator = new QIntValidator(ui->colsLE);
    colsValidator->setBottom(1);
    ui->colsLE->setValidator(colsValidator);
    ui->colsLE->setText(QString::number(m_mask->GetColsNum()));
}

// Set up Table that represent mask
void MaskSettingsDialog::SetUpTable()
{
//    ui->maskTable->clearContents();
    ui->maskTable->setRowCount(m_mask->GetRowsNum());
    ui->maskTable->setColumnCount(m_mask->GetColsNum());

    // Set up all cells
    for ( int row = 0; row < ui->maskTable->rowCount(); ++row )
    {
        for ( int col = 0; col < ui->maskTable->columnCount(); ++col )
        {
            QTableWidgetItem *item = ui->maskTable->item(row, col);
            if ( NULL == item )
            {
                item = new QTableWidgetItem();
            }

            CellType type = UNACTIVE;
            if ( m_mask->IsPixelEnabled(static_cast<unsigned int>(row),
                                        static_cast<unsigned int>(col)) )
            {
                type = ACTIVE_SIMPLE;
            }

            SetCellView(item, type);

            double weight =
                    m_mask->GetPixelWeight(static_cast<unsigned int>(row),
                                           static_cast<unsigned int>(col));

            QString weightStr = QString::number(weight);
            item->setText( weightStr );

            ui->maskTable->setItem(row, col, item);
        }
    }

    // Set up central cell
    int centralCellRow = static_cast<int>(m_mask->GetCentralPixelRow());
    int centralCellCol = static_cast<int>(m_mask->GetCentralPixelCol());
    QTableWidgetItem *centralItem =
            ui->maskTable->item(centralCellRow, centralCellCol);

    SetCellView(centralItem, ACTIVE_CENTRAL);
}

// Set view of cell on base of its type
// @input:
// - *t_item - valid pointer to cell widget
// - t_type - cell type
void MaskSettingsDialog::SetCellView(QTableWidgetItem *t_item,
                                     const CellType &t_type)
{
    if ( NULL == t_item || t_type >= DEFAULT_LAST )
    {
        qDebug() << __func__ << "Invalid arguments";
        return;
    }

    Qt::ItemFlags cellFlags = t_item->flags();
    switch(t_type)
    {
        case ACTIVE_SIMPLE:
        case ACTIVE_CENTRAL:
            cellFlags |= Qt::ItemIsEditable;
            break;

        case UNACTIVE:
            cellFlags &= ~Qt::ItemIsEditable;
            break;

        case DEFAULT_LAST:
        default:
        {
            qDebug() << __func__ << "Invalid cell type";
        }
    }

    t_item->setFlags(cellFlags);
    t_item->setBackground( GetCellColor(t_type) );
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
        case ACTIVE_SIMPLE:
            brush.setColor(Qt::white);
            break;

        case ACTIVE_CENTRAL:
            brush.setColor(Qt::red);
            break;

        case UNACTIVE:
            break;

        case DEFAULT_LAST:
        default:
        {
            qDebug() << __func__ << "Invalid cell type";
        }
    }

    return brush;
}

void MaskSettingsDialog::ChangeCellState(const unsigned int &/*t_row*/,
                                 const unsigned int &/*t_column*/,
                                 const bool &/*t_state*/)
{
//    if ( (m_rowsInMask <= t_row) || (m_columsInMask <= t_column) )
//    {
//        qDebug() << "MaskSettingsDialog::ChangeCellState(): Error - index out of range";
//        reject();
//    }

//    QTableWidgetItem *cellItem = m_maskTable->item(t_row, t_column);
//    if ( NULL == cellItem )
//    {
//        qDebug() << "MaskSettingsDialog::ChangeCellState(): Error - item is NULL (" << t_row << t_column << ")";
//        reject();
//    }

//    CellType type = DEFAULT_LAST;
//    if ( true == t_state )
//    {
//        type = ACTIVE_SIMPLE;
//    }
//    else
//    {
//        type = UNACTIVE;
//    }

//    bool stateChanged = ChangeCell(cellItem, type);
//    if ( false == stateChanged )
//    {
//        qDebug() << "MaskSettingsDialog::ChangeCellState(): Error - can't change state of cell";
//        reject();
//    }

//    // Change state of pixel in mask
//    m_mask[t_row][t_column].isEnabled = t_state;
//    m_mask[t_row][t_column].isCentral = false;
}

void MaskSettingsDialog::ChangeCentralCell(const unsigned int &/*t_row*/, const unsigned int &/*t_column*/)
{
//    if ( (m_rowsInMask <= t_row) || (m_columsInMask <= t_column) )
//    {
//        qDebug() << "MaskSettingsDialog::ChangeCentralCell(): Error - index out of range";
//        reject();
//    }

//    // Lets deactivate our current central cell
//    for (unsigned int row = 0; row < m_rowsInMask; row++)
//    {
//        for (unsigned int column = 0; column < m_columsInMask; column++)
//        {
//            if ( true == m_mask[row][column].isCentral )
//            {
//                QTableWidgetItem *oldCentralItem = m_maskTable->item(row, column);
//                if ( NULL == oldCentralItem )
//                {
//                    qDebug() << "MaskSettingsDialog::ChangeCentralCell(): Error - old central item is NULL";
//                    reject();
//                }

//                bool cellDeactivated = ChangeCell(oldCentralItem, ACTIVE_SIMPLE);
//                if ( false == cellDeactivated )
//                {
//                    qDebug() << "MaskSettingsDialog::ChangeCentralCell(): Error - can't deactivate central cell";
//                    reject();
//                }

//                m_mask[row][column].isCentral = false;
//            }
//        }
//    }

//    // And activate new central cell
//    QTableWidgetItem *newCentralItem = m_maskTable->item(t_row, t_column);
//    if ( NULL == newCentralItem )
//    {
//        qDebug() << "MaskSettingsDialog::ChangeCentralCell(): Error - new central item is NULL";
//        reject();
//    }

//    bool hasNewCentralCell = ChangeCell(newCentralItem, ACTIVE_CENTRAL);
//    if ( false == hasNewCentralCell )
//    {
//        qDebug() << "MaskSettingsDialog::ChangeCentralCell(): Error - can't set new central cell";
//        reject();
//    }

//    m_mask[t_row][t_column].isCentral = true;
//    m_mask[t_row][t_column].isEnabled = true;
}

bool MaskSettingsDialog::RebuildMask()
{
    // Lets find position of central pixel
//    int posX = 0;
//    int posY = 0;
//    bool centralPixelFound = false;

//    for (unsigned int row = 0; row < m_rowsInMask; row++)
//    {
//        for (unsigned int column = 0; column < m_columsInMask; column++)
//        {
//            if ( true == m_mask[row][column].isCentral )
//            {
//                centralPixelFound = true;

//                posX = (int)column;
//                posY = (int)row;

//                m_mask[row][column].posX = posX;
//                m_mask[row][column].posY = posY;

//                m_mask[row][column].weight = GetWeightFromCell( m_maskTable->item(row, column) );

//                break;
//            }
//        }
//    }

//    // User didn't define central pixel - emit warning
//    if ( false == centralPixelFound )
//    {
//        QMessageBox::warning(this, "Mask", "You should set central pixel");
//        return false;
//    }

    // Change offsets and weights for all other pixels
//    for (int row = 0; row < (int)m_rowsInMask; row++)
//    {
//        for (int column = 0; column < (int)m_columsInMask; column++)
//        {
//            m_mask[row][column].posX = column - posX;
//            m_mask[row][column].posY = row - posY;

//            m_mask[row][column].weight = GetWeightFromCell( m_maskTable->item(row, column) );
//        }
//    }

    return true;
}

long double MaskSettingsDialog::GetWeightFromCell(QTableWidgetItem *t_item)
{
    if ( NULL == t_item )
    {
        qDebug() << "MaskSettingsDialog::GetWeightFromCell(): Error - invalid arguments";
        return 0;
    }

    bool ok = false;
    QString textInCell = t_item->text();
    double weight = textInCell.toDouble(&ok);
    if ( true == ok )
    {
        return (long double)weight;
    }

    return 0;
}

void MaskSettingsDialog::SlotActivateCell()
{
//    unsigned int row = (unsigned int)m_maskTable->currentRow();
//    unsigned int column = (unsigned int)m_maskTable->currentColumn();
//    bool state = m_cellEnable->isChecked();

//    ChangeCellState(row, column, state);
}

void MaskSettingsDialog::SlotCenterCell()
{
//    unsigned int row = (unsigned int)m_maskTable->currentRow();
//    unsigned int column = (unsigned int)m_maskTable->currentColumn();

//    ChangeCentralCell(row, column);
}

// Slot that will be called on cell change
// @input:
// - t_row - row of changed item
// - t_col - column of changed item
void MaskSettingsDialog::SlotCellChanged(int t_row, int t_col)
{
    QTableWidgetItem *item = ui->maskTable->item(t_row, t_col);
    if ( NULL == item )
    {
        qDebug() << __func__ << "Null item";
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

void MaskSettingsDialog::SlotShowContextMenu(const QPoint &t_point)
{
    m_cellMenu.exec(ui->maskTable->viewport()->mapToGlobal(t_point));
}

void MaskSettingsDialog::on_rowsLE_editingFinished()
{
    // TODO
}

void MaskSettingsDialog::on_colsLE_editingFinished()
{
    // TODO
}
