#include "gui/noisesettingsdialog.h"
#include "ui_noisesettingsdialog.h"

#include <QStringList>
#include <QIntValidator>
#include <QDebug>

#include "common/common.h"

NoiseSettingsDialog::NoiseSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoiseSettingsDialog)
{
    ui->setupUi(this);

    ui->amplituteLE->setValidator(new QIntValidator(0, 255));
    FillNoiseTypesCB();
}

NoiseSettingsDialog::~NoiseSettingsDialog()
{
    delete ui;
}

// Fill ComboBox with noise types
void NoiseSettingsDialog::FillNoiseTypesCB()
{
    QStringList items;
    items << "Constant" << "Random" << "Absolute Random";

    ui->noiseTypeCB->addItems(items);
}

// Set noise params
// @input:
// - t_type - type of noise
// - t_amplitude - amplitude of noise
void NoiseSettingsDialog::SetNoiseParams(const Noise::Type &t_type,
                                         const int &t_amplitude)
{
    ui->noiseTypeCB->setCurrentIndex(t_type);
    ui->amplituteLE->setText(QString::number(t_amplitude));
}

// Get current noise type
// @output:
// - Noise::Type - current noise type
Noise::Type NoiseSettingsDialog::GetNoiseType() const
{
    return (Noise::Type)ui->noiseTypeCB->currentIndex();
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
void NoiseSettingsDialog::on_noiseTypeCB_currentIndexChanged(int index)
{
    if ( index < 0 || Noise::DEFAULT_LAST < index )
    {
        qDebug() << __func__ << "Error - invalid index value";
        return;
    }

    emit SignalNoiseType( (Noise::Type)index );

    if ( Noise::ABS_RANDOM == index )
    {
        ui->amplituteLE->setEnabled(false);
    }
    else
    {
        ui->amplituteLE->setEnabled(true);
    }
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
