#include "maskdialog.h"
#include "ui_maskdialog.h"

MaskDialog::MaskDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MaskDialog)
{
	ui->setupUi(this);

	m_cellEnable = NULL;
	m_cellCentral = NULL;
	m_cellMenu = NULL;
	m_maskTable = NULL;

	FindGUIElements();
	SetDefaults();
	CreateCellMenu();
}

MaskDialog::~MaskDialog()
{
	delete ui;
}

void MaskDialog::FindGUIElements()
{
	QList<QTableWidget *> tableList = this->findChildren<QTableWidget *>("maskTable");
	if ( true == tableList.isEmpty() )
	{
		qDebug() << "MaskDialog::FindGUIElements(): Error - can't find mask table!";
		emit rejected();
	}
	else
	{
		m_maskTable = tableList.at(0);
	}
}

void MaskDialog::SetDefaults()
{
	m_mask.clear();

	m_rowsInMask = 0;
	m_columsInMask = 0;

	SetTableSize();
}

void MaskDialog::CreateCellMenu()
{
	m_cellEnable = new QAction(m_maskTable);
	m_cellEnable->setText(tr("Enabled"));
	m_cellEnable->setCheckable(true);
	m_cellEnable->setChecked(false);
	connect(m_cellEnable, SIGNAL(triggered()), this, SLOT(SlotActivateCell()));

	m_cellCentral = new QAction(m_maskTable);
	m_cellCentral->setText(tr("Central"));
	m_cellCentral->setCheckable(true);
	m_cellCentral->setChecked(false);
	connect(m_cellCentral, SIGNAL(triggered()), this, SLOT(SlotCenterCell()));

	m_cellMenu = new QMenu(m_maskTable);
	m_cellMenu->addAction(m_cellEnable);
	m_cellMenu->addAction(m_cellCentral);

	m_maskTable->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(m_maskTable, SIGNAL(customContextMenuRequested(const QPoint &)),
			this, SLOT(SlotShowContextMenu(const QPoint &)));

}

void MaskDialog::SetTableSize()
{
	m_maskTable->clearContents();

	m_maskTable->setRowCount(m_rowsInMask);
	m_maskTable->setColumnCount(m_columsInMask);

	// TODO: set size of m_maskTable
}

// This signal send request to get mask params
void MaskDialog::DefineSettings()
{
	emit SignalGetMask();
}

// Fill table mask with given mask structure
void MaskDialog::FillTable()
{
	if ( true == m_mask.isEmpty() )
	{
		qDebug() << "MaskDialog::FillTable(): Error - mask is empty";
		return;
	}

	GetMaskSize();
	SetTableSize();
	FillCels();
}

void MaskDialog::GetMaskSize()
{
	if ( true == m_mask.isEmpty() )
	{
		qDebug() << "MaskDialog::GetMaskSize(): Error - mask is empty";
		SetDefaults();
		return;
	}

	QList<unsigned int> lines = m_mask.keys();

	m_rowsInMask = (unsigned int)lines.size();
	m_columsInMask = 0;

	for (unsigned int i = 0; i < m_rowsInMask; i++)
	{
		unsigned int rowLength = (unsigned int)m_mask.value(lines[i]).size();
		if ( 0 == rowLength )
		{
			qDebug() << "MaskDialog::GetMaskSize(): Error - one of the lines of mask is empty";
			SetDefaults();
		}
		else if ( m_columsInMask < rowLength )
		{
			m_columsInMask = rowLength;
		}
	}
}

void MaskDialog::FillCels()
{
	QList<unsigned int> lines = m_mask.keys();
	int maxRows = qMin( (int)m_rowsInMask, lines.size() );

	for (int row = 0; row < maxRows; row++)
	{
		QList<Mask::MasksPixel> colums = m_mask.value(row);
		int maxColums = qMin( (int)m_columsInMask, colums.size());

		for (int col = 0; col < maxColums; col++)
		{
			QString number;
			number.setNum((double)colums[col].weight);

			QTableWidgetItem *item = new QTableWidgetItem(number);
			item->setTextAlignment(Qt::AlignHCenter);

			CellType type = UNACTIVE;
			if ( true == colums[col].isEnabled )
			{
				if ( true == colums[col].isCentral )
				{
					type = ACTIVE_CENTRAL;
				}
				else
				{
					type = ACTIVE_SIMPLE;
				}
			}
			else
			{
				// Disable editing for this item
				Qt::ItemFlags flags = item->flags();
				flags = flags & ~Qt::ItemIsEditable;
				item->setFlags(flags);
//				item->setFlags(Qt::ItemIsEditable);
			}

			QBrush cellColor = SetCellColor(type);
			item->setBackground(cellColor);

			// TODO: can't add action to QTableWidgetItem. Should I change it to LineEdit?

			m_maskTable->setItem(row, col, item);
		}
	}
}

QBrush MaskDialog::SetCellColor(CellType t_type)
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
		default:
		{
			qDebug() << "MaskDialog::SetCellColor(): Error - invalid cell type";
			brush.setColor(Qt::gray);
		}
	}

	return brush;
}

void MaskDialog::ChangeCellState(const int &t_row,
								 const int &t_column,
								 const bool &t_state)
{
	if ( (t_row < 0) || (t_column < 0) )
	{
		qDebug() << "MaskDialog::ChangeCellState(): Error - index out of range";
		return;
	}

	QTableWidgetItem *cellItem = m_maskTable->item(t_row, t_column);
	if ( NULL == cellItem )
	{
		qDebug() << "MaskDialog::ChangeCellState(): Error - item is NULL (" << t_row << t_column << ")";
		return;
	}

	// Change color of the cell
	QBrush cellColor;
	if ( true == t_state )
	{
		cellColor = SetCellColor(ACTIVE_SIMPLE);
	}
	else
	{
		cellColor = SetCellColor(UNACTIVE);
	}

	cellItem->setBackground(cellColor);

	// Change cell edit property
	Qt::ItemFlags flags = cellItem->flags();
	if ( true == t_state )
	{
		flags |= Qt::ItemIsEditable;
	}
	else
	{
		flags &= ~Qt::ItemIsEditable;
	}

	cellItem->setFlags(flags);


	// Change state of pixel in mask
	m_mask[t_row][t_column].isEnabled = t_state;
}

//void MaskDialog::ChangeCentralCell(const int &t_row, const int &t_column)
//{

//}

void MaskDialog::SlotRecieveMask(QMap< unsigned int, QList<Mask::MasksPixel> > t_mask)
{
	if ( true == t_mask.isEmpty() )
	{
		qDebug() << "MaskDialog::SlotRecieveMask(): Error - mask is empty";
		return;
	}

	m_mask.clear();
	m_mask = t_mask;

	FillTable();

	emit SignalReadyToShow();
}

void MaskDialog::SlotActivateCell()
{
//	qDebug() << "SlotActivateCell()";
//	qDebug() << "Row =" << m_maskTable->currentRow() << "; Colum =" << m_maskTable->currentColumn();

	int row = m_maskTable->currentRow();
	int column = m_maskTable->currentColumn();
	bool state = m_cellEnable->isChecked();

	ChangeCellState(row, column, state);
}

void MaskDialog::SlotCenterCell()
{
	qDebug() << "SlotCenterCell()";
	qDebug() << "Row =" << m_maskTable->currentRow() << "; Colum =" << m_maskTable->currentColumn();
}

void MaskDialog::SlotShowContextMenu(const QPoint &t_point)
{
	int row = m_maskTable->currentRow();
	int column = m_maskTable->currentColumn();

	if ( true == m_mask[row].at(column).isEnabled )
	{
		m_cellEnable->setChecked(true);
	}
	else
	{
		m_cellEnable->setChecked(false);
	}

	if ( true == m_mask[row].at(column).isCentral )
	{
		m_cellCentral->setChecked(true);
	}
	else
	{
		m_cellCentral->setChecked(false);
	}

	m_cellMenu->exec(m_maskTable->viewport()->mapToGlobal(t_point));
}

// User pressed "OK" button
void MaskDialog::on_buttonBox_accepted()
{
	emit SignalReturnMask(m_mask);
}

// User pressed "Cancel" button
void MaskDialog::on_buttonBox_rejected()
{

}
