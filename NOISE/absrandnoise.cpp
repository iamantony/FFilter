#include "absrandnoise.h"

QImage AbsRandNoise::GetNoisedImage()
{
    if ( true == m_imgToNoise.isNull() )
    {
        qDebug() << "AbsRandNoise::NoiseImage(): Error - invalid arguments";
        return m_imgToNoise;
    }

    QList<int> noiseForPixels = GenerateNoise();
    int pixelsToNoise = noiseForPixels.size();
    int noisedPixelNum = 0;
    int imgW = m_imgToNoise.width();
    int imgH = m_imgToNoise.height();
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
            if ( (m_needToNoise == m_pixelsToChange[w][h]) &&
                 ( noisedPixelNum < pixelsToNoise ) )
            {
                pixelLum = noiseForPixels.at(noisedPixelNum);
                noisedPixelNum++;

                pixel = qRgb(pixelLum, pixelLum, pixelLum);
                m_imgToNoise.setPixel(w, h, pixel);
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

    return m_imgToNoise;
}

QList<int> AbsRandNoise::GenerateNoise()
{
    srand(time(NULL));
    int randLuminance = 0;
    const int maxLuminance = 256;
    QList<int> listOfNoise;

    for (unsigned int i = 0; i < m_pixelsToNoise; i++ )
    {
        randLuminance = rand() % maxLuminance;
        listOfNoise.append(randLuminance);
    }

    return listOfNoise;
}
