#ifndef MASKDIALOG_H
#define MASKDIALOG_H

#include <QDialog>
#include <QList>
#include <QTableWidget>
#include <QDebug>
#include "DEFINES/common.h"
#include "DEFINES/mask.h"

namespace Ui {
	class MaskDialog;
}

class MaskDialog : public QDialog
{
	Q_OBJECT

	// == DATA ==
private:
	Ui::MaskDialog *ui;
	QList<Mask::MasksPixel> m_mask;
	QTableWidget *m_maskTable;
	unsigned int m_rowsInMask;
	unsigned int m_columsInMask;

	// == METHODS ==
public:
	explicit MaskDialog(QWidget *parent = 0);
	~MaskDialog();

	// This signal send request to get mask
	void DefineSettings();

private:
	void FindGUIElements();
	void SetDefaults();

signals:
	void SignalGetMaskParams();
	void SignalReturnMaskParams(unsigned int t_rows,
								unsigned int t_colums,
								QList<Mask::MasksPixel> t_mask);

public slots:
	void SlotRecieveMaskParams(unsigned int t_rows,
							   unsigned int t_colums,
							   QList<Mask::MasksPixel> t_mask);

private slots:
	// User pressed "OK" button
	void on_buttonBox_accepted();
	// User pressed "Cancel" button
	void on_buttonBox_rejected();
};

#endif // MASKDIALOG_H
