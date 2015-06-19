#include "noisegenerator.h"

#include <QScopedPointer>
#include <QDebug>

#include "noise/noise.h"
#include "noise/abstractnoise.h"
#include "noise/constnoise.h"
#include "noise/randnoise.h"
#include "noise/absrandnoise.h"

NoiseGenerator::NoiseGenerator(QObject *parent) :
    QObject(parent)
{
    m_noiseType = Noise::CONSTANT;
    m_noiseAmp = 0;
    m_noiseLvlPercent = 0;
}

NoiseGenerator::~NoiseGenerator()
{
}

// Set noise type
// @input:
// - t_type - noise type
void NoiseGenerator::SetNoiseType(const Noise::Type &t_type)
{
    m_noiseType = t_type;
}

// Get current noise type
// @output:
// - Noise::Type - current noise type
Noise::Type NoiseGenerator::GetNoiseType() const
{
    return m_noiseType;
}

// Set noise amplitude
// @input:
// - t_type - noise amplitude within [0, 255]
void NoiseGenerator::SetNoiseAmplitude(const int &t_amp)
{
    if ( t_amp < Noise::MIN_NOISE_AMP || Noise::MAX_NOISE_AMP < t_amp )
    {
        qDebug() << __func__ << "Invalid noise amplitude";
        return;
    }

    m_noiseAmp = t_amp;
}

// Get current noise amplitude
// @output:
// - int - value of current noise amplitude
int NoiseGenerator::GetNoiseAmplitude() const
{
    return m_noiseAmp;
}

// Set level of noise
// @input:
// - t_level - noise level within [0, 100]
void NoiseGenerator::SetNoiseLevel(const unsigned int &t_level)
{
    if ( 100 < t_level )
    {
        m_noiseLvlPercent = 100;
    }
    else
    {
        m_noiseLvlPercent = t_level;
    }
}

// Apply noise to image
// @input:
// - t_img - valid image that should be noised
// @output:
// - QImage - copy of input image with noise
QImage NoiseGenerator::NoiseImage(const QImage &t_img)
{
    QScopedPointer<AbstractNoise> noise;
    switch(m_noiseType)
    {
        case Noise::CONSTANT:
        {
            noise.reset(new ConstNoise(t_img,
                                       m_noiseLvlPercent,
                                       m_noiseAmp));

            break;
        }

        case Noise::RANDOM:
        {
            noise.reset(new RandNoise(t_img,
                                      m_noiseLvlPercent,
                                      m_noiseAmp));

            break;
        }

        case Noise::ABS_RANDOM:
        {
            noise.reset(new AbsRandNoise(t_img,
                                         m_noiseLvlPercent,
                                         m_noiseAmp));
            break;
        }

        case Noise::DEFAULT_LAST:
        default:
        {
            QImage sameImg = t_img;
            return sameImg;
        }
    }

    connect(noise.data(), SIGNAL(SignalProgressPrc(int)),
            this, SLOT(SlotGetProgressPrc(int)));

    QImage noisedImg = noise->GetNoisedImage();

    noise->disconnect(SIGNAL(SignalProgressPrc(int)));

    if ( true == noisedImg.isNull() )
    {
        QImage sameImg = t_img;
        return sameImg;
    }

    return noisedImg;
}

// Slot for transmitting progress percent
// @input:
// - t_progress - progress percent
void NoiseGenerator::SlotGetProgressPrc(int t_progress)
{
    emit SignalProgressPrc(t_progress);
}
