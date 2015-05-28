#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QString>

#include "aggreg_operators/aggreg_operators.h"

namespace Ui
{
    class AggregFilterSettingsDialog;
}

class AggregFilterSettingsDialog : public QDialog
{
    Q_OBJECT

    // == METHODS ==
public:
    explicit AggregFilterSettingsDialog(QWidget *parent = 0);
    ~AggregFilterSettingsDialog();

    // Set active aggregation operator type
    void SetCurrAggrOpType(const AggregOperator::Type::Type &t_type);
    // Set aggregation operator power
    void SetCurrAggrOpPower(const double &t_power);
    // Set active aggregation operator function type
    void SetCurrAggrOpFunc(const AggregOperator::Func::Type &t_type);

private:
    // Fill ComboBox for aggregation operators types
    void FillAggrOpCB();
    // Fill ComboBox for functions for functional aggregation operator
    void FillAggrOpFuncsCB();

signals:
    void SignalAggrOpType(AggregOperator::Type::Type t_type);
    void SignalAggrOpPower(double t_power);
    void SignalAggrOpFunc(AggregOperator::Func::Type t_func);

private slots:
    // Slot that will be called on change of aggregation operator type
    void on_aggrOpCB_currentIndexChanged(int index);
    // Slot that will be called on change of power value
    void on_powerLE_editingFinished();
    // Slot that will be called on change of functional aggregation operator
    // type
    void on_funcTypeCB_currentIndexChanged(int index);

    // == DATA ==
private:
    Ui::AggregFilterSettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
