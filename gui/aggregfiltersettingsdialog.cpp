#include "aggregfiltersettingsdialog.h"
#include "ui_aggregfiltersettingsdialog.h"

#include <QDoubleValidator>
#include <QDebug>

#include "gui/cblistmodel.h"

template<>
void CBListModel<AggregOperator::Type>::init()
{
    m_data <<
        QPair<AggregOperator::Type, QString>(
                AggregOperator::Type::MIN, "Min") <<

        QPair<AggregOperator::Type, QString>(
                AggregOperator::Type::MAX, "Max") <<

        QPair<AggregOperator::Type, QString>(
                AggregOperator::Type::MEAN, "Mean") <<

        QPair<AggregOperator::Type, QString>(
                AggregOperator::Type::GEOMETRIC_MEAN, "Geometric Mean") <<

        QPair<AggregOperator::Type, QString>(
                AggregOperator::Type::HARMONC_MAEN, "Harmonic Mean") <<

        QPair<AggregOperator::Type, QString>(
                AggregOperator::Type::MEDIAN, "Median") <<

        QPair<AggregOperator::Type, QString>(
                AggregOperator::Type::FUNCTIONAL, "Functional");
}

template<>
void CBListModel<AggregOperator::Func>::init()
{
    m_data <<
        QPair<AggregOperator::Func, QString>(
                AggregOperator::Func::EXP, "Exponential") <<

        QPair<AggregOperator::Func, QString>(
                AggregOperator::Func::LOG_NATURAL, "Logarithm");
}

AggregFilterSettingsDialog::AggregFilterSettingsDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::AggregFilterSettingsDialog)
{
    ui->setupUi(this);

    ui->powerLE->setValidator(new QDoubleValidator());
    FillAggrOpCB();
    FillAggrOpFuncsCB();
}

AggregFilterSettingsDialog::~AggregFilterSettingsDialog()
{
    delete ui;
}

// Fill ComboBox with aggregation operators types
void AggregFilterSettingsDialog::FillAggrOpCB()
{
    CBListModel<AggregOperator::Type>* model =
            new CBListModel<AggregOperator::Type>(this);
    model->init();

    ui->aggrOpCB->setModel(model);
}

// Fill ComboBox with function types of functional aggregation operator
void AggregFilterSettingsDialog::FillAggrOpFuncsCB()
{
    CBListModel<AggregOperator::Func>* model =
            new CBListModel<AggregOperator::Func>(this);
    model->init();

    ui->funcTypeCB->setModel(model);
}

// Set active aggregation operator type
// @input:
// - t_type - valid aggregation operator type
void AggregFilterSettingsDialog::SetCurrAggrOpType(
        const AggregOperator::Type &t_type)
{
    CBListModel<AggregOperator::Type>* model =
        dynamic_cast<CBListModel<AggregOperator::Type>*>(ui->aggrOpCB->model());
    if ( nullptr == model )
    {
        qDebug() << __FUNCTION__ << "Failed to get model";
        return;
    }

    ui->aggrOpCB->setCurrentIndex( model->getIndex(t_type) );
}

// Get current aggregation operator type
// @output:
// - AggregOperator::Type::Type - current aggregation operator type
AggregOperator::Type AggregFilterSettingsDialog::GetAggrOpType() const
{
    CBListModel<AggregOperator::Type>* model =
        dynamic_cast<CBListModel<AggregOperator::Type>*>(ui->aggrOpCB->model());
    if ( nullptr == model )
    {
        qDebug() << __FUNCTION__ << "Failed to get model";
        return AggregOperator::Type::MIN;
    }

    return model->getType(ui->aggrOpCB->currentText());
}

// Set aggregation operator power
// @input:
// - t_power - aggregation operator power
void AggregFilterSettingsDialog::SetCurrAggrOpPower(const double &t_power)
{
    ui->powerLE->setText(QString::number(t_power));
}

// Get current aggregation operator power value
// @output:
// - double - current power value
double AggregFilterSettingsDialog::GetAggrOpPower() const
{
    bool transformed = false;
    double power = ui->powerLE->displayText().toDouble(&transformed);
    if ( transformed )
    {
        return power;
    }

    return 0.0;
}

// Set active functional aggregation operator type
// @input:
// - t_type - valid functional aggregation operator type
void AggregFilterSettingsDialog::SetCurrAggrOpFunc(
        const AggregOperator::Func &t_type)
{
    CBListModel<AggregOperator::Func>* model =
        dynamic_cast<CBListModel<AggregOperator::Func>*>(
                ui->funcTypeCB->model());
    if ( nullptr == model )
    {
        qDebug() << __FUNCTION__ << "Failed to get model";
        return;
    }

    ui->funcTypeCB->setCurrentIndex( model->getIndex(t_type) );
}

// Get current aggregation operator function type
// @output:
// - AggregOperator::Func::Type - current aggregation operator function type
AggregOperator::Func AggregFilterSettingsDialog::GetAggrOpFunc() const
{
    CBListModel<AggregOperator::Func>* model =
        dynamic_cast<CBListModel<AggregOperator::Func>*>(
                ui->funcTypeCB->model());
    if ( nullptr == model )
    {
        qDebug() << __FUNCTION__ << "Failed to get model";
        return AggregOperator::Func::EXP;
    }

    return model->getType(ui->funcTypeCB->currentText());
}

// Slot that will be called on change of aggregation operator type
// @input:
// - text - current name of the aggregation operator type in combobox
void AggregFilterSettingsDialog::on_aggrOpCB_currentIndexChanged(
        const QString& text)
{
    CBListModel<AggregOperator::Type>* model =
        dynamic_cast<CBListModel<AggregOperator::Type>*>(ui->aggrOpCB->model());
    if ( nullptr == model )
    {
        qDebug() << __FUNCTION__ << "Failed to get model";
        return;
    }

    AggregOperator::Type type = model->getType(text);
    emit SignalAggrOpType( type );

    // User can choose function type only when aggregation operator is
    // functional
    ui->funcTypeCB->setEnabled( AggregOperator::Type::FUNCTIONAL == type );

    // User can change power of function only when aggregation operator is mean
    ui->powerLE->setEnabled( AggregOperator::Type::MEAN == type );
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
// - text - current name of the functional aggregation operator type in combobox
void AggregFilterSettingsDialog::on_funcTypeCB_currentIndexChanged(
        const QString& text)
{
    CBListModel<AggregOperator::Func>* model =
        dynamic_cast<CBListModel<AggregOperator::Func>*>(
                ui->funcTypeCB->model());
    if ( nullptr == model )
    {
        qDebug() << __FUNCTION__ << "Failed to get model";
        return;
    }

    emit SignalAggrOpFunc( model->getType(text) );
}
