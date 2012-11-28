#include "randnoise.h"

QImage RandNoise::GetNoisedImage()
{
	if ( true == m_imgToNoise.isNull() )
	{
		qDebug() << "AbsRandNoise::NoiseImage(): Error - invalid arguments";
		return m_imgToNoise;
	}

	// Noise without amplitude is not the noise at all
	if ( 0 == m_noiseAmplitude )
	{
		return m_imgToNoise;
	}

	QList<int> noiseForPixels = GenerateNoise();
	int pixelsToNoise = noiseForPixels.size();
	int noisedPixelNum = 0;
	int imgW = m_imgToNoise.width();
	int imgH = m_imgToNoise.height();
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
			if ( (m_needToNoise == m_pixelsToChange[w][h]) &&
				 ( noisedPixelNum < pixelsToNoise ) )
			{
				oldPixel = m_imgToNoise.pixel(w, h);
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
				m_imgToNoise.setPixel(w, h, newPixel);
			}

			counter++;
			if ( counter == onePercent )
			{
				counter = 0;
				progressPrc++;
				emit SignalProcProgressPrc(progressPrc);
			}
		}
	}

	return m_imgToNoise;
}

QList<int> RandNoise::GenerateNoise()
{
	srand(time(NULL));
	int randLuminance = 0;
	const int maxDeviation = qAbs(m_noiseAmplitude);
	int sign = 1;
	if ( m_noiseAmplitude < 0 )
	{
		sign = -1;
	}

	QList<int> listOfNoise;

	for (unsigned int i = 0; i < m_pixelsToNoise; i++ )
	{
		randLuminance = rand() % maxDeviation;
		randLuminance *= sign;
		listOfNoise.append(randLuminance);
	}

	return listOfNoise;
}
