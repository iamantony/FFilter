#include "gui/noisesettingsdialog.h"
#include "ui_noisesettingsdialog.h"

#include <QIntValidator>
#include <QDebug>

#include "gui/cblistmodel.h"

template<>
void CBListModel<Noise::Type>::init()
{
    m_data << QPair<Noise::Type, QString>(Noise::Type::CONSTANT, "Constant") <<
        QPair<Noise::Type, QString>(Noise::Type::RANDOM, "Random") <<
        QPair<Noise::Type, QString>(Noise::Type::ABS_RANDOM, "Absolute Random");
}

NoiseSettingsDialog::NoiseSettingsDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::NoiseSettingsDialog)
{
    ui->setupUi(this);

    ui->amplituteLE->setValidator(new QIntValidator(-255, 255));
    FillNoiseTypesCB();
}

NoiseSettingsDialog::~NoiseSettingsDialog()
{
    delete ui;
}

// Fill ComboBox with noise types
void NoiseSettingsDialog::FillNoiseTypesCB()
{
    CBListModel<Noise::Type>* model = new CBListModel<Noise::Type>(this);
    model->init();

    ui->noiseTypeCB->setModel(model);
}

// Set noise params
// @input:
// - t_type - type of noise
// - t_amplitude - amplitude of noise
void NoiseSettingsDialog::SetNoiseParams(const Noise::Type& t_type,
                                         const int& t_amplitude)
{
    CBListModel<Noise::Type>* model =
        dynamic_cast<CBListModel<Noise::Type>*>(ui->noiseTypeCB->model());
    if ( nullptr == model )
    {
        qDebug() << __FUNCTION__ << "Failed to get model";
        return;
    }

    ui->noiseTypeCB->setCurrentIndex( model->getIndex(t_type) );
    ui->amplituteLE->setText(QString::number(t_amplitude));
}

// Get current noise type
// @output:
// - Noise::Type - current noise type
Noise::Type NoiseSettingsDialog::GetNoiseType() const
{
    CBListModel<Noise::Type>* model =
        dynamic_cast<CBListModel<Noise::Type>*>(ui->noiseTypeCB->model());
    if ( nullptr == model )
    {
        qDebug() << __FUNCTION__ << "Failed to get model";
        return Noise::Type::CONSTANT;
    }

    return model->getType(ui->noiseTypeCB->currentText());
}

// Get current noise amplitude
// @output:
// - int - current noise amplitude
int NoiseSettingsDialog::GetNoiseAmplitude() const
{
    bool transformed = false;
    int amplitude = ui->amplituteLE->displayText().toInt(&transformed);
    if ( transformed )
    {
        return amplitude;
    }

    return 0;
}

// Slot that will be called on change of noise type
// @input:
// - index - index of noise type
void NoiseSettingsDialog::on_noiseTypeCB_currentIndexChanged(
        const QString& text)
{
    CBListModel<Noise::Type>* model =
        dynamic_cast<CBListModel<Noise::Type>*>(ui->noiseTypeCB->model());
    if ( nullptr == model )
    {
        qDebug() << __FUNCTION__ << "Failed to get model";
        return;
    }

    Noise::Type type = model->getType(text);
    emit SignalNoiseType(type);

    ui->amplituteLE->setEnabled( Noise::Type::ABS_RANDOM == type );
}

// Slot that will be called on change of noise amplitude
void NoiseSettingsDialog::on_amplituteLE_editingFinished()
{
    bool transformed = false;
    int amplitude = ui->amplituteLE->displayText().toInt(&transformed);
    if ( transformed )
    {
        emit SignalNoiseAmplitude(amplitude);
    }
    else
    {
        ui->amplituteLE->setText("");
    }
}
