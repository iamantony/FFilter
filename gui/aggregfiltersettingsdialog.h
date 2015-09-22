#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

#include "aggreg_operators/aggregoperators.h"

namespace Ui
{
    class AggregFilterSettingsDialog;
}

class AggregFilterSettingsDialog : public QDialog
{
    Q_OBJECT

    // == METHODS ==
public:
    explicit AggregFilterSettingsDialog(QWidget* parent = 0);
    virtual ~AggregFilterSettingsDialog();

    // Set active aggregation operator type
    void SetCurrAggrOpType(const AggregOperator::Type& t_type);
    // Get current aggregation operator type
    AggregOperator::Type GetAggrOpType() const;
    // Set aggregation operator power
    void SetCurrAggrOpPower(const double& t_power);
    // Get current aggregation operator power value
    double GetAggrOpPower() const;
    // Set active aggregation operator function type
    void SetCurrAggrOpFunc(const AggregOperator::Func& t_type);
    // Get current aggregation operator function type
    AggregOperator::Func GetAggrOpFunc() const;

private:
    // Fill ComboBox with aggregation operators types
    void FillAggrOpCB();
    // Fill ComboBox with function types of functional aggregation operator
    void FillAggrOpFuncsCB();

signals:
    void SignalAggrOpType(AggregOperator::Type t_type);
    void SignalAggrOpPower(double t_power);
    void SignalAggrOpFunc(AggregOperator::Func t_func);

private slots:
    // Slot that will be called on change of aggregation operator type
    void on_aggrOpCB_currentIndexChanged(const QString& text);
    // Slot that will be called on change of power value
    void on_powerLE_editingFinished();
    // Slot that will be called on change of functional aggregation operator
    // type
    void on_funcTypeCB_currentIndexChanged(const QString& text);

    // == DATA ==
private:
    Ui::AggregFilterSettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
