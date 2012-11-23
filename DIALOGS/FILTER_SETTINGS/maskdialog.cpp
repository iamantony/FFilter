#include "maskdialog.h"
#include "ui_maskdialog.h"

MaskDialog::MaskDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MaskDialog)
{
	ui->setupUi(this);
	FindGUIElements();
	SetDefaults();
}

MaskDialog::~MaskDialog()
{
	SetDefaults();
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

void MaskDialog::CreateCellMenu()
{
	m_cellActive.setText("Pixel is active");

	m_cellEnable.setText("Pixel is enabled");

//	m_cellMenu.addAction()
}

void MaskDialog::SetDefaults()
{
	m_mask.clear();

	m_rowsInMask = 0;
	m_columsInMask = 0;

	SetTableSize();
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

// User pressed "OK" button
void MaskDialog::on_buttonBox_accepted()
{
	emit SignalReturnMask(m_mask);
}

// User pressed "Cancel" button
void MaskDialog::on_buttonBox_rejected()
{

}
