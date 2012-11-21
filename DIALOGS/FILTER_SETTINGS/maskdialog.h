#ifndef MASKDIALOG_H
#define MASKDIALOG_H

#include <QDialog>

namespace Ui {
	class MaskDialog;
}

class MaskDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit MaskDialog(QWidget *parent = 0);
	~MaskDialog();
	
private:
	Ui::MaskDialog *ui;
};

#endif // MASKDIALOG_H
