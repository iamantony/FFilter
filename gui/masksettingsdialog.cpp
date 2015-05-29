#include "gui/masksettingsdialog.h"
#include "ui_masksettingsdialog.h"

#include <QBrush>
#include <QColor>
#include <QMessageBox>
#include <QDebug>

MaskSettingsDialog::MaskSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaskSettingsDialog)
{
    ui->setupUi(this);

    SetDefaults();
    CreateCellMenu();

    this->setAttribute(Qt::WA_DeleteOnClose);
}

MaskSettingsDialog::~MaskSettingsDialog()
{
    delete ui;
}

void MaskSettingsDialog::SetDefaults()
{
    m_mask.clear();

    m_rowsInMask = 0;
    m_columsInMask = 0;

    m_cellEnable = NULL;
    m_cellCentral = NULL;
    m_cellMenu = NULL;

    SetTableSize();
}

void MaskSettingsDialog::CreateCellMenu()
{
    m_cellMenu = new QMenu(ui->maskTable);

    // This action will enable (if checked)/disable (if unchecked) cell
    m_cellEnable = new QAction(m_cellMenu);
    m_cellEnable->setText(tr("Enabled"));
    m_cellEnable->setCheckable(true);
    m_cellEnable->setChecked(false);
    connect(m_cellEnable, SIGNAL(triggered()), this, SLOT(SlotActivateCell()));

    // This action will make any cell central
    m_cellCentral = new QAction(m_cellMenu);
    m_cellCentral->setText(tr("Central"));
    m_cellCentral->setCheckable(true);
    m_cellCentral->setChecked(false);
    connect(m_cellCentral, SIGNAL(triggered()), this, SLOT(SlotCenterCell()));

    m_cellMenu->addAction(m_cellEnable);
    m_cellMenu->addAction(m_cellCentral);

    ui->maskTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->maskTable, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(SlotShowContextMenu(const QPoint &)));
}

void MaskSettingsDialog::SetTableSize()
{
    ui->maskTable->clearContents();

    ui->maskTable->setRowCount(m_rowsInMask);
    ui->maskTable->setColumnCount(m_columsInMask);

    // TODO: user could set size of m_maskTable
}

// This signal send request to get mask params
void MaskSettingsDialog::DefineSettings()
{
    emit SignalGetMask();
}

// Fill table mask with given mask structure
void MaskSettingsDialog::FillTable()
{
    if ( true == m_mask->IsEmpty() )
    {
        qDebug() << "MaskSettingsDialog::FillTable(): Error - mask is empty";
        return;
    }

    GetMaskSize();
    SetTableSize();
    FillCels();
}

void MaskSettingsDialog::GetMaskSize()
{
//    if ( true == m_mask.IsEmpty() )
//    {
//        qDebug() << "MaskSettingsDialog::GetMaskSize(): Error - mask is empty";
//        SetDefaults();
//        return;
//    }

//    QList<unsigned int> lines = m_mask.keys();

//    m_rowsInMask = (unsigned int)lines.size();
//    m_columsInMask = 0;

//    for (unsigned int i = 0; i < m_rowsInMask; i++)
//    {
//        unsigned int rowLength = (unsigned int)m_mask.value(lines[i]).size();
//        if ( 0 == rowLength )
//        {
//            qDebug() << "MaskSettingsDialog::GetMaskSize(): Error - one of the lines of mask is empty";
//            SetDefaults();
//        }
//        else if ( m_columsInMask < rowLength )
//        {
//            m_columsInMask = rowLength;
//        }
//    }
}

// Fill cells and set their view by info from mask
void MaskSettingsDialog::FillCels()
{
//    QList<unsigned int> lines = m_mask.keys();
//    int maxRows = qMin( (int)m_rowsInMask, lines.size() );

//    for (int row = 0; row < maxRows; row++)
//    {
//        QList<Mask::MasksPixel> colums = m_mask.value(row);
//        int maxColums = qMin( (int)m_columsInMask, colums.size());

//        for (int col = 0; col < maxColums; col++)
//        {
//            QString number;
//            number.setNum((double)colums[col].weight);

//            QTableWidgetItem *item = new QTableWidgetItem(number);
//            item->setTextAlignment(Qt::AlignHCenter);

//            CellType type = UNACTIVE;
//            if ( true == colums[col].isEnabled )
//            {
//                if ( true == colums[col].isCentral )
//                {
//                    type = ACTIVE_CENTRAL;
//                }
//                else
//                {
//                    type = ACTIVE_SIMPLE;
//                }
//            }

//            bool hasNewCell = ChangeCell(item, type);
//            if ( false == hasNewCell )
//            {
//                qDebug() << "MaskSettingsDialog::FillCels(): Error - can't set new cell";
//                reject();
//            }

//            m_maskTable->setItem(row, col, item);
//        }
//    }
}

QBrush MaskSettingsDialog::SetCellColor(CellType t_type)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    switch(t_type)
    {
        case ACTIVE_SIMPLE:
            brush.setColor(Qt::white);
            break;

        case ACTIVE_CENTRAL:
            brush.setColor(Qt::red);
            break;

        case UNACTIVE:
            brush.setColor(Qt::gray);
            break;

        case DEFAULT_LAST:
        default:
        {
            qDebug() << "MaskSettingsDialog::SetCellColor(): Error - invalid cell type";
            brush.setColor(Qt::gray);
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

bool MaskSettingsDialog::ChangeCell(QTableWidgetItem *t_item, CellType t_type)
{
    if ( (NULL == t_item) || ( t_type >= DEFAULT_LAST) )
    {
        qDebug() << "MaskSettingsDialog::ChangeCell(): Error - invalid arguments";
        return false;
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
            qDebug() << "MaskSettingsDialog::ChangeCell(): Error - invalid cell type";
            return false;
        }
    }

    t_item->setFlags(cellFlags);

    QBrush backgroundColor = SetCellColor(t_type);
    t_item->setBackground(backgroundColor);

    return true;
}

bool MaskSettingsDialog::RebuildMask()
{
    // Lets find position of central pixel
//    int posX = 0;
//    int posY = 0;
    bool centralPixelFound = false;

    for (unsigned int row = 0; row < m_rowsInMask; row++)
    {
        for (unsigned int column = 0; column < m_columsInMask; column++)
        {
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
        }
    }

    // User didn't define central pixel - emit warning
    if ( false == centralPixelFound )
    {
        QMessageBox::warning(this, "Mask", "You should set central pixel");
        return false;
    }

    // Change offsets and weights for all other pixels
    for (int row = 0; row < (int)m_rowsInMask; row++)
    {
        for (int column = 0; column < (int)m_columsInMask; column++)
        {
//            m_mask[row][column].posX = column - posX;
//            m_mask[row][column].posY = row - posY;

//            m_mask[row][column].weight = GetWeightFromCell( m_maskTable->item(row, column) );
        }
    }

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

//void MaskSettingsDialog::SlotRecieveMask(QMap< unsigned int, QList<Mask::MasksPixel> > t_mask)
//{
//    if ( true == t_mask.isEmpty() )
//    {
//        qDebug() << "MaskSettingsDialog::SlotRecieveMask(): Error - mask is empty";
//        return;
//    }

//    m_mask.clear();
//    m_mask = t_mask;

//    FillTable();

//    show();
//}

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

void MaskSettingsDialog::SlotShowContextMenu(const QPoint &/*t_point*/)
{
//    int row = m_maskTable->currentRow();
//    int column = m_maskTable->currentColumn();

//    if ( true == m_mask[row].at(column).isEnabled )
//    {
//        m_cellEnable->setChecked(true);
//    }
//    else
//    {
//        m_cellEnable->setChecked(false);
//    }

//    if ( true == m_mask[row].at(column).isCentral )
//    {
//        m_cellCentral->setChecked(true);
//    }
//    else
//    {
//        m_cellCentral->setChecked(false);
//    }

//    m_cellMenu->exec(m_maskTable->viewport()->mapToGlobal(t_point));
}

void MaskSettingsDialog::on_buttonBox_accepted()
{
    if ( RebuildMask() )
    {
//        emit SignalReturnMask(m_mask);
        accept();
    }
}
