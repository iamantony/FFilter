#include "noise/constnoise.h"

#include <QColor>
#include <QDebug>

ConstNoise::ConstNoise(const QImage &t_img,
                       const unsigned int &t_noiseLvl,
                       const int &t_noiseAmp) :
    AbstractNoise(t_img, t_noiseLvl, t_noiseAmp)
{
}

ConstNoise::~ConstNoise()
{
}

QImage ConstNoise::GetNoisedImage()
{
    if ( true == m_img.isNull() )
    {
        qDebug() << "AbsRandNoise::NoiseImage(): Error - invalid arguments";
        return m_img;
    }

    // Noise without amplitude is not the noise at all
    if ( 0 == m_noiseAmplitude )
    {
        return m_img;
    }

    QList<int> noiseForPixels = GenerateNoise();
    int pixelsToNoise = noiseForPixels.size();
    int noisedPixelNum = 0;
    int imgW = m_img.width();
    int imgH = m_img.height();
    int pixelLum = 0;
    QRgb newPixel;
    QColor oldPixel;

    int onePercent = ( imgW * imgH ) / 100;
    int progressPrc = 0;
    int counter = 0;

    // Start algorith
    for ( int w = 0; w < imgW; w++ )
    {
        for ( int h = 0; h < imgH; h++ )
        {
            if ( (m_needToNoise == m_pixelsMap[w][h]) &&
                 ( noisedPixelNum < pixelsToNoise ) )
            {
                oldPixel = m_img.pixel(w, h);
                pixelLum = oldPixel.red() + noiseForPixels.at(noisedPixelNum);
                noisedPixelNum++;

                if ( 255 < pixelLum )
                {
                    pixelLum = 255;
                }
                else if ( pixelLum < 0 )
                {
                    pixelLum = 0;
                }

                newPixel = qRgb(pixelLum, pixelLum, pixelLum);
                m_img.setPixel(w, h, newPixel);
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

QList<int> ConstNoise::GenerateNoise()
{
    QList<int> listOfNoise;
    for (unsigned int i = 0; i < m_pixelsToNoise; i++ )
    {
        listOfNoise.append(m_noiseAmplitude);
    }

    return listOfNoise;
}
