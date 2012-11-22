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
	m_rowsInMask = 0;
	m_columsInMask = 0;

	m_maskTable->setRowCount(m_rowsInMask);
	m_maskTable->setColumnCount(m_columsInMask);
}

// This signal send request to get mask params
void MaskDialog::DefineSettings()
{
	emit SignalGetMaskParams();
}

// Fill table mask with given mask structure
//void MaskDialog::FillTable()
//{

//}

void MaskDialog::SlotRecieveMaskParams(unsigned int t_rows,
									   unsigned int t_colums,
									   QList<Mask::MasksPixel> t_mask)
{
	if ( true == t_mask.isEmpty() )
	{
		qDebug() << "MaskDialog::SlotRecieveMask(): Error - mask is empty";
		return;
	}

	m_mask.clear();
	m_mask = t_mask;

	// TODO: this not right thing!
	t_rows = t_colums;

//	FillTable();
}

// User pressed "OK" button
void MaskDialog::on_buttonBox_accepted()
{
	emit SignalReturnMaskParams(m_rowsInMask, m_columsInMask, m_mask);
}

// User pressed "Cancel" button
void MaskDialog::on_buttonBox_rejected()
{

}
