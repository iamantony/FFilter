#ifndef NOISEDIALOG_H
#define NOISEDIALOG_H

#include <QDialog>

#include "noise/noise.h"

namespace Ui
{
    class NoiseSettingsDialog;
}

class NoiseSettingsDialog : public QDialog
{
    Q_OBJECT

    // == METHODS ==
public:
    explicit NoiseSettingsDialog(QWidget *parent = 0);
    virtual ~NoiseSettingsDialog();

    // Set noise params
    void SetNoiseParams(const Noise::Type &t_type, const int &t_amplitude);
    // Get current noise type
    Noise::Type GetNoiseType() const;
    // Get current noise amplitude
    int GetNoiseAmplitude() const;

private:
    // Fill ComboBox with noise types
    void FillNoiseTypesCB();

signals:
    void SignalNoiseType(Noise::Type t_noiseType);
    void SignalNoiseAmplitude(int t_amplitude);

private slots:
    // Slot that will be called on change of noise type
    void on_noiseTypeCB_currentIndexChanged(int index);
    // Slot that will be called on change of noise amplitude
    void on_amplituteLE_editingFinished();

    // == DATA ==
private:
    Ui::NoiseSettingsDialog *ui;
};

#endif // NOISEDIALOG_H
