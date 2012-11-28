#include "defaultnoise.h"

DefaultNoise::DefaultNoise(const QImage &t_img,
						   const unsigned int &t_noiseLvl,
						   const int &t_noiseAmp ,
						   QObject *parent)
{
	if ( true == t_img.isNull() )
	{
		qDebug() << "DefaultNoise(): Error - invalid arguments";
		m_noiseAmplitude = 0;
		m_noiseLevelPercent = 0;
		return;
	}

	m_imgToNoise = t_img;

	if ( 100 < t_noiseLvl )
	{
		m_noiseLevelPercent = 100;
	}
	else
	{
		m_noiseLevelPercent = t_noiseLvl;
	}

	m_noiseAmplitude = t_noiseAmp;
	this->setParent(parent);

	// If noiseLvl > 50% we invert an algorith. What does it mean? Well, in usual way (noiseLvl < 50%) we choose
	// noiseLvl% of pixels and add noise to them. But when noiseLvl > 50% this algorithm is quite slow. It's easier
	// to choose noiseLvl% of pixels and DON'T noise them.
	m_needToNoise = true;
	if ( 50 < m_noiseLevelPercent )
	{
		m_noiseLevelPercent = 100 - m_noiseLevelPercent;
		m_needToNoise = false;
	}

	unsigned int numOfPixelsInImg = m_imgToNoise.width() * m_imgToNoise.height();
	m_numPixToChange = ( m_noiseLevelPercent * numOfPixelsInImg) / 100;
	if ( true == m_needToNoise )
	{
		m_pixelsToNoise = m_numPixToChange;
	}
	else
	{
		m_pixelsToNoise = numOfPixelsInImg - m_numPixToChange;
	}

	m_pixelsToChange = NULL;

	CreateImgNoiseMap();
}

DefaultNoise::~DefaultNoise()
{
	if ( NULL == m_pixelsToChange )
	{
		return;
	}

	for (int line = 0; line < m_imgToNoise.width(); line++)
	{
		delete [] m_pixelsToChange[line];
	}

	delete [] m_pixelsToChange;
}

void DefaultNoise::CreateImgNoiseMap()
{
	srand(time(NULL));

	if ( true ==  m_imgToNoise.isNull() )
	{
		qDebug() << "DefaultNoise::CreateImgNoiseMap(): Error - can't create noise map for NULL image";
		return;
	}

	int imgW = m_imgToNoise.width();
	int imgH = m_imgToNoise.height();

	// This bool mass help us to noise pixels only once.
	m_pixelsToChange = new bool* [imgW];
	for ( int pix = 0; pix < imgW; pix++ )
	{
		m_pixelsToChange[pix] = new bool [imgH];
	}

	// Set default value
	for ( int w = 0; w < imgW; w++ )
	{
		for ( int h = 0; h < imgH; h++ )
		{
			m_pixelsToChange[w][h] = false;
		}
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

			if ( false == m_pixelsToChange[wRand][hRand] )
			{
				m_pixelsToChange[wRand][hRand] = true;
				break;
			}
		}
		while( 1 );
	}
}
