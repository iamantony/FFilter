#include "maskdialog.h"
#include "ui_maskdialog.h"

MaskDialog::MaskDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MaskDialog)
{
	ui->setupUi(this);
}

MaskDialog::~MaskDialog()
{
	delete ui;
}
