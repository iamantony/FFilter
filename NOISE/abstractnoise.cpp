#include "noise/abstractnoise.h"

#include <time.h>

#include <QDebug>

const int minNoiseAmp = -255;
const int maxNoiseAmp = 255;
const unsigned int maxPercent = 100;

AbstractNoise::AbstractNoise(const QImage &t_img,
                             const unsigned int &t_noiseLvl,
                             const int &t_noiseAmp) :
    m_needToNoise(false), m_noiseAmplitude(0), m_pixelsToNoise(0)
{
    if ( true == t_img.isNull() )
    {
        qDebug() << __func__ << "Invalid arguments";
        return;
    }

    m_img = t_img;

    m_noiseAmplitude = t_noiseAmp;
    if ( m_noiseAmplitude < minNoiseAmp )
    {
        m_noiseAmplitude = minNoiseAmp;
    }
    else if ( maxNoiseAmp < m_noiseAmplitude )
    {
        m_noiseAmplitude = maxNoiseAmp;
    }

    CreatePixelsMap(t_noiseLvl);
}

AbstractNoise::~AbstractNoise()
{
}

// Create map of pixels by whitch we can define should this pixel be noised
// or not
// @input:
// - t_noiseLvl - noise level in percents (number of pixels in percents that
// should be noised)
void AbstractNoise::CreatePixelsMap(const unsigned int &t_noiseLvl)
{
    // Set how many pixels should be noised in percents and set pixels default
    // value - "not noised"
    unsigned int pixelsToChangePrc = qMin(t_noiseLvl, maxPercent);
    bool isPixelNoised = false;

    // If pixelsToChangePrc is more than a half of the max value ( 100% ),
    // than noise algorithm would work faster if we set pixels default values
    // to "noised" and than "denoise" some of the pixels
    if ( (maxPercent / 2) < pixelsToChangePrc )
    {
        pixelsToChangePrc = maxPercent - pixelsToChangePrc;
        isPixelNoised = true;
    }

    int imgW = m_img.width();
    int imgH = m_img.height();
    unsigned int pixelsToChange = ( pixelsToChangePrc * (imgW * imgH)) / 100;

    // Create pixels map with default value
    for ( int w = 0; w < imgW; ++w )
    {
        m_pixelsMap << QVector<bool>(imgH, isPixelNoised);
    }

    // Change default value of calculated number of pixels
    srand(time(NULL));
    int wRand = 0;
    int hRand = 0;
    for ( unsigned int pix = 0; pix < pixelsToChange; ++pix )
    {
        while(true)
        {
            wRand = rand() % imgW;
            hRand = rand() % imgH;
            if ( isPixelNoised == m_pixelsMap.at(wRand).at(hRand) )
            {
                m_pixelsMap[wRand][hRand] = !isPixelNoised;
                break;
            }
        }
    }
}
