#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QMap>
#include <QString>

#include "DEFINES/common.h"
#include "DEFINES/enums.h"

#define STR_MIN "Min"
#define STR_MAX "Max"
#define STR_MEAN "Mean"
#define STR_GEOM_MEAN "Geometric Mean"
#define STR_HARM_MEAN "Harmonic Mean"
#define STR_MEDIAN "Median"
#define STR_FUNC "Functional"

#define STR_EXP "Exponential"
#define STR_LN "Logarithm"

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

    void SetCurrAggrOp(AggregOperatorType::AggrOpType t_type);
    void SetCurrAggrOpPower(const double &t_power);
    void SetCurrAggrOpFunc(AggregOperatorFunc::AggrOpFunc t_func);

private:
    void Init();
    void SetDefaults();
    // Fill list of aggregation operators types
    void SetAggrOpList();
    // Fill list of functions for functional aggregation operator
    void SetAggrOpFuncList();
    // Fill ComboBox for aggregation operators types
    void FillAggrOpCB();
    // Fill ComboBox for functions for functional aggregation operator
    void FillAggrOpFuncsCB();
    // Find position of mean agrreg. operator in ComboBox
    void FindMeanAgOp();
    // Find position of functional agrreg. operator in ComboBox
    void FindFunctionalAgOp();

signals:
    void SignalAggrOpType(AggregOperatorType::AggrOpType t_type);
    void SignalAggrOpPower(double t_power);
    void SignalAggrOpFunc(AggregOperatorFunc::AggrOpFunc t_func);

private slots:
    // User changed type of aggreg. operator and we need to enable/disable some UI elements
    void on_aggrOpCB_currentIndexChanged(int index);
    // User changed type of aggreg. operator
    void on_aggrOpCB_currentIndexChanged(const QString &arg1);
    // User changed type of function for functional aggreg. operator
    void on_funcCB_currentIndexChanged(const QString &arg1);
    // User changed value of power
    void on_powerLE_editingFinished();
    // User pressed "OK" button
    void on_buttonBox_accepted();

    // == DATA ==
private:
    Ui::AggregFilterSettingsDialog *ui;

    QMap<AggregOperatorType::AggrOpType, QString> m_aggrOpTypesMap;
    QMap<AggregOperatorFunc::AggrOpFunc, QString> m_aggrOpFuncsMap;

    AggregOperatorType::AggrOpType m_currAggrOpType;
    AggregOperatorFunc::AggrOpFunc m_currAggrOpFunc;
    double m_currAggrOpPower;

    int m_posOfFuncAggrOp;
    int m_posOfMeanAggrOp;
};

#endif // SETTINGSDIALOG_H
