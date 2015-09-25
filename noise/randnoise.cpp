#include "noise/randnoise.h"

#include <time.h>

#include <QVector>

RandNoise::RandNoise(const QImage &t_img,
                     const unsigned int &t_noiseLvl,
                     const int &t_noiseAmp) :
    AbstractNoise(t_img, t_noiseLvl, t_noiseAmp)
{
}

// Generate noise values
// @output:
// - QVector<int> - noise values
QVector<int> RandNoise::GenerateNoise()
{
    srand(time(NULL));
    const int maxDeviation = qAbs(m_noiseAmplitude);
    int sign = 1;
    if ( m_noiseAmplitude < 0 )
    {
        sign = -1;
    }

    unsigned int pixelsToNoise = GetNumOfPixelsToNoise();
    QVector<int> noise(pixelsToNoise, 0);
    for (unsigned int i = 0; i < pixelsToNoise; ++i )
    {
        noise[i] = (rand() % maxDeviation) * sign;
    }

    return noise;
}
