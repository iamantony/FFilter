#ifndef MASKDIALOG_H
#define MASKDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QMenu>
#include <QAction>
#include <QSharedPointer>

#include "masks/mask.h"

namespace Ui
{
    class MaskSettingsDialog;
}

class MaskSettingsDialog : public QDialog
{
    Q_OBJECT

    // == DATA ==
private:
    Ui::MaskSettingsDialog *ui;
    QSharedPointer<Mask> m_mask;
    QMenu m_cellMenu;
    QAction m_cellEnable;
    QAction m_cellCentral;

    enum CellType
    {
        ACTIVE_SIMPLE = 0,
        ACTIVE_CENTRAL,
        UNACTIVE,
        DEFAULT_LAST
    };

    // == METHODS ==
public:
    explicit MaskSettingsDialog(QSharedPointer<Mask> t_mask,
                                QWidget *parent = 0);
    virtual ~MaskSettingsDialog();

private:
    // Create menu widget
    void CreateCellMenu();
    // Set to gui elements size of mask
    void SetMaskSizeValues();
    // Set up Table that represent mask
    void SetUpTable();
    // Set view of cell on base of its type
    void SetCellView(QTableWidgetItem *t_item, const CellType &t_type);
    // Get color of cell
    QBrush GetCellColor(const CellType &t_type);
    void ChangeCellState(const unsigned int &t_row,
                         const unsigned int &t_column,
                         const bool &t_state);

    void ChangeCentralCell(const unsigned int &t_row, const unsigned int &t_column);

    bool RebuildMask();
    long double GetWeightFromCell(QTableWidgetItem *t_item);

private slots:
    void SlotActivateCell();
    void SlotCenterCell();
    // Slot that will be called on cell change
    void SlotCellChanged(int t_row, int t_col);
    void SlotShowContextMenu(const QPoint &t_point);
    void on_rowsLE_textEdited();
    void on_colsLE_textEdited();
};

#endif // MASKDIALOG_H
