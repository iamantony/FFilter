#ifndef NOISEDIALOG_H
#define NOISEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QMap>

#include "noise/noise.h"

#define STR_CONST "Constant"
#define STR_RAND "Random"
#define STR_ABS_RAND "Absolute Random"

namespace Ui {
    class NoiseDialog;
}

class NoiseDialog : public QDialog
{
    Q_OBJECT

    // == DATA ==
private:
    Ui::NoiseDialog *ui;
    QComboBox *m_noiseTypeCB;
    QLineEdit *m_ampLE;
    Noise::Type m_noise;
    int m_amplitude;
    QMap<Noise::Type, QString> m_noiseTypesMap;
    int m_posOfAbsRandNoise;

    // == METHODS ==
public:
    explicit NoiseDialog(QWidget *parent);
    ~NoiseDialog();
    void SetNoiseParams(Noise::Type t_type, const int &t_ampl);

private:
    void Init();
    void FindGUIElements();
    void SetNoiseTypesList();
    void FillNoiseTypesCB();
    void FindAbsRandNoise();
    void SetNoiseType();
    void SetNoiseAmp();

signals:
    void SignalNewNoiseType(Noise::Type t_noise);
    void SignalNewNoiseAmp(int t_amp);

private slots:
    void on_noiseTypeCB_currentIndexChanged(int index);
    void on_noiseTypeCB_currentIndexChanged(const QString &arg1);
    void on_ampLE_editingFinished();
    void on_okBtn_clicked();
    void on_cancelBtn_clicked();
    virtual void accept();
    virtual void reject();
};

#endif // NOISEDIALOG_H
