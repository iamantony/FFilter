#include "noise/absrandnoise.h"

#include <time.h>

#include <QDebug>

AbsRandNoise::AbsRandNoise(const QImage &t_img,
                           const unsigned int &t_noiseLvl,
                           const int &t_noiseAmp) :
    AbstractNoise(t_img, t_noiseLvl, t_noiseAmp)
{
}

AbsRandNoise::~AbsRandNoise()
{
}

QImage AbsRandNoise::GetNoisedImage()
{
    if ( true == m_img.isNull() )
    {
        qDebug() << "AbsRandNoise::NoiseImage(): Error - invalid arguments";
        return m_img;
    }

    QVector<int> noiseForPixels = GenerateNoise();
    int pixelsToNoise = noiseForPixels.size();
    int noisedPixelNum = 0;
    int imgW = m_img.width();
    int imgH = m_img.height();
    int pixelLum = 0;
    QRgb pixel;

    int onePercent = ( imgW * imgH ) / 100;
    int progressPrc = 0;
    int counter = 0;

    // Start algorith
    for ( int w = 0; w < imgW; w++ )
    {
        for ( int h = 0; h < imgH; h++ )
        {
            if ( m_pixelsMap[w][h] && noisedPixelNum < pixelsToNoise )
            {
                pixelLum = noiseForPixels.at(noisedPixelNum);
                noisedPixelNum++;

                pixel = qRgb(pixelLum, pixelLum, pixelLum);
                m_img.setPixel(w, h, pixel);
            }

            counter++;
            if ( counter == onePercent )
            {
                counter = 0;
                progressPrc++;
                emit SignalProgressPrc(progressPrc);
            }
        }
    }

    return m_img;
}

QVector<int> AbsRandNoise::GenerateNoise()
{
    srand(time(NULL));
    int randLuminance = 0;
    const int maxLuminance = 256;
    QVector<int> listOfNoise;

    for (unsigned int i = 0; i < GetNumOfPixelsToNoise(); i++ )
    {
        randLuminance = rand() % maxLuminance;
        listOfNoise.append(randLuminance);
    }

    return listOfNoise;
}
