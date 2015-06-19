#include "noise/abstractnoise.h"

#include <time.h>

#include <QColor>
#include <QDebug>

#include "noise/noise.h"

AbstractNoise::AbstractNoise(const QImage &t_img,
                             const unsigned int &t_noiseLvl,
                             const int &t_noiseAmp) :
    m_noiseAmplitude(0)
{
    if ( true == t_img.isNull() )
    {
        qDebug() << __func__ << "Invalid arguments";
        return;
    }

    m_img = t_img;

    m_noiseAmplitude = t_noiseAmp;
    if ( m_noiseAmplitude < Noise::MIN_NOISE_AMP )
    {
        m_noiseAmplitude = Noise::MIN_NOISE_AMP;
    }
    else if ( Noise::MAX_NOISE_AMP < m_noiseAmplitude )
    {
        m_noiseAmplitude = Noise::MAX_NOISE_AMP;
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
    unsigned int pixelsToChangePrc = qMin(t_noiseLvl, Noise::MAX_PERCENT);
    bool isPixelNoised = false;

    // If pixelsToChangePrc is more than a half of the max value ( 100% ),
    // than noise algorithm would work faster if we set pixels default values
    // to "noised" and than "denoise" some of the pixels
    if ( (Noise::MAX_PERCENT / 2) < pixelsToChangePrc )
    {
        pixelsToChangePrc = Noise::MAX_PERCENT - pixelsToChangePrc;
        isPixelNoised = true;
    }

    int imgW = m_img.width();
    int imgH = m_img.height();
    unsigned int pixelsToChange =
            ( pixelsToChangePrc * (imgW * imgH)) / Noise::MAX_PERCENT;

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

// Get noised copy of image
// @ouput:
// - QImage - noised copy of image. Or original image in case of some error
QImage AbstractNoise::GetNoisedImage()
{
    if ( m_img.isNull() )
    {
        qDebug() << __func__ << "Image is empty";
        return m_img;
    }

    if ( 0 == m_noiseAmplitude )
    {
        return m_img;
    }

    QVector<int> noise = GenerateNoise();
    const int pixelsToNoise = noise.size();
    int noisedPixelNum = 0;
    int imgW = m_img.width();
    int imgH = m_img.height();

    int onePercent = ( imgW * imgH ) / Noise::MAX_PERCENT;
    int progressPrc = 0;
    int counter = 0;

    for ( int w = 0; w < imgW; ++w )
    {
        for ( int h = 0; h < imgH; ++h )
        {
            if ( m_pixelsMap.at(w).at(h) && noisedPixelNum < pixelsToNoise )
            {
                QColor oldPixel = m_img.pixel(w, h);
                int pixelLum = oldPixel.red() + noise.at(noisedPixelNum);
                pixelLum = qMin(pixelLum, Noise::MAX_LUMINANCE);
                pixelLum = qMax(pixelLum, Noise::MIN_LUMINANCE);

                QRgb newPixel = qRgb(pixelLum, pixelLum, pixelLum);
                m_img.setPixel(w, h, newPixel);
                ++noisedPixelNum;
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

// Get number of pixels that should be noised
// @output:
// - unsigned int - number of pixels that should be noised
unsigned int AbstractNoise::GetNumOfPixelsToNoise() const
{
    unsigned int pixelsNum = 0;
    for ( int i = 0; i < m_pixelsMap.size(); ++i )
    {
        pixelsNum += m_pixelsMap.at(i).count(true);
    }

    return pixelsNum;
}
