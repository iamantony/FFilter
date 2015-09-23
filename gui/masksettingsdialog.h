#ifndef MASKDIALOG_H
#define MASKDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>
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

    enum class CellType
    {
        ENABLED = 0,
        CENTRAL,
        DISABLED,
        DEFAULT_LAST
    };

    // == METHODS ==
public:
    explicit MaskSettingsDialog(QSharedPointer<Mask> t_mask,
                                QWidget *parent = 0);
    virtual ~MaskSettingsDialog();

private:
    // Set to gui elements size of mask
    void SetMaskSizeValues();
    // Set up Table that represent mask
    void SetUpTable();
    // Set view of mask item on base of its type
    void SetItemView(QTableWidgetItem *t_item);
    // Get color of cell
    QBrush GetCellColor(const CellType &t_type);

private slots:
    // Slot that will be called on cell change
    void SlotCellChanged(int t_row, int t_col);
    // Slot that will show menu
    void SlotShowContextMenu(const QPoint &t_point);
    // Slot that will be called on row number change
    void on_rowsLE_textEdited();
    // Slot that will be called on columns number change
    void on_colsLE_textEdited();
};

#endif // MASKDIALOG_H
