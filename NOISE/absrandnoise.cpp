#include "noise/absrandnoise.h"

#include <time.h>

#include "noise/noise.h"

AbsRandNoise::AbsRandNoise(const QImage &t_img,
                           const unsigned int &t_noiseLvl,
                           const int &t_noiseAmp) :
    AbstractNoise(t_img, t_noiseLvl, t_noiseAmp)
{
}

// Generate noise values
// @output:
// - QVector<int> - noise values
QVector<int> AbsRandNoise::GenerateNoise()
{
    srand(time(NULL));

    unsigned int pixelsToNoise = GetNumOfPixelsToNoise();
    QVector<int> noise(pixelsToNoise, 0);
    for (unsigned int i = 0; i < pixelsToNoise; ++i )
    {
        noise[i] = rand() % Noise::MAX_LUMINANCE;
    }

    return noise;
}
