#include "noise/abstractnoise.h"

#include <time.h>

#include <QDebug>

AbstractNoise::AbstractNoise(const QImage &t_img,
                             const unsigned int &t_noiseLvl,
                             const int &t_noiseAmp) :
    m_needToNoise(false), m_noiseAmplitude(0), m_noiseLevelPercent(0),
    m_pixelsToNoise(0), m_numPixToChange(0)
{
    if ( true == t_img.isNull() )
    {
        qDebug() << __func__ << "Invalid arguments";
        return;
    }

    m_img = t_img;
    m_noiseAmplitude = t_noiseAmp;

    if ( 100 < t_noiseLvl )
    {
        m_noiseLevelPercent = 100;
    }
    else
    {
        m_noiseLevelPercent = t_noiseLvl;
    }

    // If noiseLvl > 50% we invert an algorith. What does it mean?
    // If noiseLvl < 50% we choose noiseLvl% of pixels and add noise to them.
    // But when noiseLvl > 50%, algorithm becomes slower and slower. In this
    // case it's faster to choose (100 - noiseLvl)% of pixels that we
    // WOULD NOT noise.
    m_needToNoise = true;
    if ( 50 < m_noiseLevelPercent )
    {
        m_noiseLevelPercent = 100 - m_noiseLevelPercent;
        m_needToNoise = false;
    }

    unsigned int pixelsInImg = m_img.width() * m_img.height();
    m_numPixToChange = ( m_noiseLevelPercent * pixelsInImg) / 100;
    if ( true == m_needToNoise )
    {
        m_pixelsToNoise = m_numPixToChange;
    }
    else
    {
        m_pixelsToNoise = pixelsInImg - m_numPixToChange;
    }

    CreatePixelsMap();
}

AbstractNoise::~AbstractNoise()
{
}

// Create map of pixels by whitch we can define should this pixel be noised
// or not
void AbstractNoise::CreatePixelsMap()
{
    srand(time(NULL));

    if ( true ==  m_img.isNull() )
    {
        qDebug() << __func__ << "Can't create pixels map for empty image";
        return;
    }

    int imgW = m_img.width();
    int imgH = m_img.height();

    for ( int w = 0; w < imgW; ++w )
    {
        m_pixelsMap << QVector<bool>(imgH, false);
    }

    // Then by random we choose pixels and define their fate:
    // - if noiseLvl < 50%, then they will be noised
    // - if noiseLvl > 50%, then they value will be saved (and unchoosed will be noised)
    int wRand = 0;
    int hRand = 0;
    for ( unsigned int pix = 0; pix < m_numPixToChange; pix++ )
    {
        do
        {
            wRand = rand() % imgW;
            hRand = rand() % imgH;

            if ( false == m_pixelsMap.at(wRand).at(hRand) )
            {
                m_pixelsMap[wRand][hRand] = true;
                break;
            }
        }
        while( true );
    }
}
