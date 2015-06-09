#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H

#include <QObject>
#include <QImage>

#include "noise.h"

class NoiseGenerator : public QObject
{
    Q_OBJECT

    // == METHODS ==
public:
    explicit NoiseGenerator(QObject *parent = 0);
    virtual ~NoiseGenerator();

    // Set noise type
    void SetNoiseType(const Noise::Type &t_type);
    // Get current noise type
    Noise::Type GetNoiseType() const;
    // Set noise amplitude
    void SetNoiseAmplitude(const int &t_amp);
    // Get current noise amplitude
    int GetNoiseAmplitude() const;
    // Set level of noise
    void SetNoiseLevel(const unsigned int &t_level);
    // Apply noise to image
    QImage NoiseImage(const QImage &t_img);

signals:
    void SignalProgressPrc(int t_progress);

public slots:
    // Slot for transmitting progress percent
    void SlotGetProgressPrc(int t_progress);

    // == DATA ==
private:
    Noise::Type m_noiseType;
    int m_noiseAmp;
    unsigned int m_noiseLvlPercent;
};

#endif // NOISEGENERATOR_H
