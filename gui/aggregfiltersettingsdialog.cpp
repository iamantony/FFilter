#include "aggregfiltersettingsdialog.h"
#include "ui_aggregfiltersettingsdialog.h"

#include <QDebug>

#include "common/common.h"

AggregFilterSettingsDialog::AggregFilterSettingsDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::AggregFilterSettingsDialog)
{
    ui->setupUi(this);

    Init();
}

AggregFilterSettingsDialog::~AggregFilterSettingsDialog()
{
    delete ui;
}

void AggregFilterSettingsDialog::Init()
{
    SetDefaults();
    SetAggrOpList();
    SetAggrOpFuncList();
    FindMeanAgOp();
    FindFunctionalAgOp();
}

void AggregFilterSettingsDialog::SetDefaults()
{
    m_currAggrOpType = AggregOperator::Type::MIN;
    m_currAggrOpFunc = AggregOperator::Func::EXP;
    m_currAggrOpPower = 1;

    m_posOfFuncAggrOp = ERROR;
    m_posOfMeanAggrOp = ERROR;
}

// Fill list of aggregation operators types
void AggregFilterSettingsDialog::SetAggrOpList()
{
    m_aggrOpTypesMap.insert(AggregOperator::Type::MIN, STR_MIN);
    m_aggrOpTypesMap.insert(AggregOperator::Type::MAX, STR_MAX);
    m_aggrOpTypesMap.insert(AggregOperator::Type::MEAN, STR_MEAN);
    m_aggrOpTypesMap.insert(AggregOperator::Type::GEOMETRIC_MEAN, STR_GEOM_MEAN);
    m_aggrOpTypesMap.insert(AggregOperator::Type::HARMONC_MAEN, STR_HARM_MEAN);
    m_aggrOpTypesMap.insert(AggregOperator::Type::MEDIAN, STR_MEDIAN);
    m_aggrOpTypesMap.insert(AggregOperator::Type::FUNCTIONAL, STR_FUNC);

    FillAggrOpCB();
}

// Fill ComboBox for aggregation operators types
void AggregFilterSettingsDialog::FillAggrOpCB()
{
    if ( true == m_aggrOpTypesMap.isEmpty() )
    {
        qDebug() << "AggregFilterSettingsDialog::FillAggrOpCB(): Error - map is empty";
        reject();
    }

    QList<QString> listOfTypes = m_aggrOpTypesMap.values();
    for (int type = 0; type < listOfTypes.size(); type++)
    {
        ui->aggrOpCB->addItem(listOfTypes.at(type));
    }
}

// Fill list of functions for functional aggregation operator
void AggregFilterSettingsDialog::SetAggrOpFuncList()
{
    m_aggrOpFuncsMap.insert(AggregOperator::Func::EXP, STR_EXP);
    m_aggrOpFuncsMap.insert(AggregOperator::Func::LOG_NATURAL, STR_LN);

    FillAggrOpFuncsCB();
}

// Fill ComboBox for functions for functional aggregation operator
void AggregFilterSettingsDialog::FillAggrOpFuncsCB()
{
    if ( true == m_aggrOpFuncsMap.isEmpty() )
    {
        qDebug() << "FillAggrOpFuncsCB(): Error - map is empty";
        reject();
    }

    QList<QString> listOfFuncs = m_aggrOpFuncsMap.values();
    for (int func = 0; func < listOfFuncs.size(); func++)
    {
        ui->funcTypeCB->addItem(listOfFuncs.at(func));
    }
}

// Find position of mean agrreg. operator in ComboBox
void AggregFilterSettingsDialog::FindMeanAgOp()
{
    int position = ui->aggrOpCB->findText(STR_MEAN);
    if ( ERROR == position )
    {
        qDebug() << "FindFunctionalAgOp(): Error - can't find position of" << STR_MEAN;
        reject();
    }
    else
    {
        m_posOfMeanAggrOp = position;
    }
}

// Find position of functional agrreg. operator in ComboBox
void AggregFilterSettingsDialog::FindFunctionalAgOp()
{
    int position = ui->aggrOpCB->findText(STR_FUNC);
    if ( ERROR == position )
    {
        qDebug() << "FindFunctionalAgOp(): Error - can't find position of" << STR_FUNC;
        reject();
    }
    else
    {
        m_posOfFuncAggrOp = position;
    }
}

void AggregFilterSettingsDialog::SetCurrAggrOp(
        const AggregOperator::Type::Type &t_type)
{
    QString typeName = m_aggrOpTypesMap.value(t_type);
    int posOfType = ui->aggrOpCB->findText(typeName);
    if ( ERROR == posOfType )
    {
        qDebug() <<
            "SetCurrAggrOp(): Error - can't find type of aggreg operator:" <<
            t_type;
        reject();
    }
    else
    {
        m_currAggrOpType = t_type;
        ui->aggrOpCB->setCurrentIndex(posOfType);
    }
}

void AggregFilterSettingsDialog::SetCurrAggrOpPower(const double &t_power)
{
    m_currAggrOpPower = t_power;
    ui->powerLE->setText(QString::number(m_currAggrOpPower));
}

void AggregFilterSettingsDialog::SetCurrAggrOpFunc(
        const AggregOperator::Func::Type &t_func)
{
    QString funcName = m_aggrOpFuncsMap.value(t_func);
    int posOfFunc = ui->funcTypeCB->findText(funcName);
    if ( ERROR == posOfFunc )
    {
        qDebug() <<
            "SetCurrAggrOpFunc(): Error - can't find type of function:" <<
            t_func;
        reject();
    }
    else
    {
        m_currAggrOpFunc = t_func;
        ui->funcTypeCB->setCurrentIndex(posOfFunc);
    }
}

// User changed type of aggreg. operator and we need to enable/disable some UI elements
void AggregFilterSettingsDialog::on_aggrOpCB_currentIndexChanged(int index)
{
    // User should have choise of function only when aggregation operator is functional
    if ( index == m_posOfFuncAggrOp )
    {
        ui->funcTypeCB->setEnabled(true);
    }
    else
    {
        ui->funcTypeCB->setEnabled(false);
    }

    // User can change power of function only when aggregation operator is power
    if ( index == m_posOfMeanAggrOp )
    {
        ui->powerLE->setEnabled(true);
    }
    else
    {
        ui->powerLE->setEnabled(false);
    }
}

// User changed type of aggreg. operator
void AggregFilterSettingsDialog::on_aggrOpCB_currentIndexChanged(const QString &arg1)
{
    QList<QString> listOfTypes = m_aggrOpTypesMap.values();
    for (int type = 0; type < listOfTypes.size(); type++)
    {
        if ( arg1 == listOfTypes.at(type) )
        {
            m_currAggrOpType = m_aggrOpTypesMap.key(listOfTypes.at(type));
            break;
        }
    }
}

// User changed type of function for functional aggreg. operator
void AggregFilterSettingsDialog::on_funcCB_currentIndexChanged(const QString &arg1)
{
    QList<QString> listOfFunc = m_aggrOpFuncsMap.values();

    for (int func = 0; func < listOfFunc.size(); func++)
    {
        if ( arg1 == listOfFunc.at(func) )
        {
            m_currAggrOpFunc = m_aggrOpFuncsMap.key(listOfFunc.at(func));
            break;
        }
    }
}

// User changed value of power
void AggregFilterSettingsDialog::on_powerLE_editingFinished()
{
    bool transformed = false;
    double power = ui->powerLE->displayText().toDouble(&transformed);
    if ( false == transformed )
    {
        ui->powerLE->setText(QString::number(m_currAggrOpPower));
    }
    else
    {
        m_currAggrOpPower = power;
    }
}

// User pressed "OK" button
void AggregFilterSettingsDialog::on_buttonBox_accepted()
{
    emit SignalAggrOpType(m_currAggrOpType);
    emit SignalAggrOpPower(m_currAggrOpPower);
    emit SignalAggrOpFunc(m_currAggrOpFunc);

    accept();
}
