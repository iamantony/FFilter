#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H

#include <QObject>
#include <QImage>
#include <QDebug>
#include "defaultnoise.h"
#include "constnoise.h"
#include "randnoise.h"
#include "absrandnoise.h"
#include "noise.h"

class NoiseGenerator : public QObject
{
    Q_OBJECT

    // == DATA ==
private:
    Noise::Type m_noiseType;
    int m_noiseAmp;
    unsigned int m_noiseLvlPercent;
    DefaultNoise *m_noiseGenerator;

    // == METHODS ==
public:
    explicit NoiseGenerator(QObject *parent = 0);
    ~NoiseGenerator();

    void SetNoiseType(Noise::Type t_type);
    Noise::Type GetNoiseType();
    void SetNoiseAmplitude(const int &t_amp);
    int GetNoiseAmplitude();
    void SetNoiseLevel(const unsigned int &t_level);
    QImage SetNoiseToImg(const QImage &t_img);

signals:
    void SignalProcProgressPrc(int t_progress);

public slots:
    void SlotGetProgressBarValue(int t_progress);
};

#endif // NOISEGENERATOR_H
