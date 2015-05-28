#include "aggregfiltersettingsdialog.h"
#include "ui_aggregfiltersettingsdialog.h"

#include <QDebug>

#include "common/common.h"

AggregFilterSettingsDialog::AggregFilterSettingsDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::AggregFilterSettingsDialog)
{
    ui->setupUi(this);

    FillAggrOpCB();
    FillAggrOpFuncsCB();
}

AggregFilterSettingsDialog::~AggregFilterSettingsDialog()
{
    delete ui;
}

// Fill ComboBox for aggregation operators types
void AggregFilterSettingsDialog::FillAggrOpCB()
{
    QStringList items;
    items
            << "Min"
            << "Max"
            << "Mean"
            << "Geometric Mean"
            << "Harmonic Mean"
            << "Median"
            << "Functional"
               ;

    ui->aggrOpCB->addItems( items );
}

// Fill ComboBox for functions for functional aggregation operator
void AggregFilterSettingsDialog::FillAggrOpFuncsCB()
{
    QStringList items;
    items
            << "Exponential"
            << "Logarithm"
               ;

    ui->funcTypeCB->addItems( items );
}

// Set active aggregation operator type
// @input:
// - t_type - valid aggregation operator type
void AggregFilterSettingsDialog::SetCurrAggrOpType(
        const AggregOperator::Type::Type &t_type)
{
    ui->aggrOpCB->setCurrentIndex( (int)t_type );
}

// Set aggregation operator power
// @input:
// - t_power - aggregation operator power
void AggregFilterSettingsDialog::SetCurrAggrOpPower(const double &t_power)
{
    ui->powerLE->setText(QString::number(t_power));
}

// Set active functional aggregation operator type
// @input:
// - t_type - valid functional aggregation operator type
void AggregFilterSettingsDialog::SetCurrAggrOpFunc(
        const AggregOperator::Func::Type &t_type)
{
    ui->funcTypeCB->setCurrentIndex( (int)t_type );
}

// Slot that will be called on change of aggregation operator type
// @input:
// - index - index of aggregation operator type
void AggregFilterSettingsDialog::on_aggrOpCB_currentIndexChanged(int index)
{
    // TODO: redo
    AggregOperator::Type::Type type = static_cast<AggregOperator::Type::Type>(index);
    emit SignalAggrOpType(type);

    // User can choose function type only when aggregation operator is
    // functional
    if ( AggregOperator::Type::FUNCTIONAL == type )
    {
        ui->funcTypeCB->setEnabled(true);
    }
    else
    {
        ui->funcTypeCB->setEnabled(false);
    }

    // User can change power of function only when aggregation operator is mean
    if ( AggregOperator::Type::MEAN == type )
    {
        ui->powerLE->setEnabled(true);
    }
    else
    {
        ui->powerLE->setEnabled(false);
    }
}

// Slot that will be called on change of power value
void AggregFilterSettingsDialog::on_powerLE_editingFinished()
{
    bool transformed = false;
    double power = ui->powerLE->displayText().toDouble(&transformed);
    if ( transformed )
    {
        emit SignalAggrOpPower(power);
    }
    else
    {
        ui->powerLE->setText("");
    }
}

// Slot that will be called on change of functional aggregation operator
// type
// @input:
// - index - index of functional aggregation operator type
void AggregFilterSettingsDialog::on_funcTypeCB_currentIndexChanged(int index)
{
    // TODO: redo
    emit SignalAggrOpFunc( (AggregOperator::Func::Type)index );
}
