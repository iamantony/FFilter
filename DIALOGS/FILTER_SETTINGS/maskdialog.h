#ifndef MASKDIALOG_H
#define MASKDIALOG_H

#include <QDialog>
#include <QList>
#include <QMap>
#include <QTableWidget>
#include <QBrush>
#include <QColor>
#include <QMenu>
#include <QAction>
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
	QMenu *m_cellMenu;
	QAction *m_cellEnable;
	QAction *m_cellCentral;
	QMap<unsigned int, QList<Mask::MasksPixel> > m_mask;
	QTableWidget *m_maskTable;
	unsigned int m_rowsInMask;
	unsigned int m_columsInMask;

	enum CellType
	{
		ACTIVE_SIMPLE = 0,
		ACTIVE_CENTRAL,
		UNACTIVE,
		DEFAULT_LAST
	};

	// == METHODS ==
public:
	explicit MaskDialog(QWidget *parent = 0);
	~MaskDialog();

	// This signal send request to get mask
	void DefineSettings();

private:
	void FindGUIElements();
	void SetDefaults();
	void CreateCellMenu();
	void SetTableSize();
	// Fill table mask with given mask structure
	void FillTable();
	void GetMaskSize();
	void FillCels();
	QBrush SetCellColor(CellType t_type);
	void ChangeCellState(const int &t_row,
						 const int &t_column,
						 const bool &t_state);

	void ChangeCentralCell(const int &t_row, const int &t_column);

signals:
	void SignalGetMask();
	void SignalReturnMask(QMap<unsigned int, QList<Mask::MasksPixel> > t_mask);
	void SignalReadyToShow();

public slots:
	void SlotRecieveMask(QMap<unsigned int, QList<Mask::MasksPixel> > t_mask);

private slots:
	void SlotActivateCell();
	void SlotCenterCell();
	void SlotShowContextMenu(const QPoint &t_point);
	// User pressed "OK" button
	void on_buttonBox_accepted();
	// User pressed "Cancel" button
	void on_buttonBox_rejected();
};

#endif // MASKDIALOG_H
