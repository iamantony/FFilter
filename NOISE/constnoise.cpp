#include "noise/constnoise.h"

#include <QVector>

ConstNoise::ConstNoise(const QImage &t_img,
                       const unsigned int &t_noiseLvl,
                       const int &t_noiseAmp) :
    AbstractNoise(t_img, t_noiseLvl, t_noiseAmp)
{
}

ConstNoise::~ConstNoise()
{
}

// Generate noise values
// @output:
// - QVector<int> - noise values
QVector<int> ConstNoise::GenerateNoise()
{
    return QVector<int>(GetNumOfPixelsToNoise(), m_noiseAmplitude);
}
