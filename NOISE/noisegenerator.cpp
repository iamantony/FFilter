#include "noisegenerator.h"

NoiseGenerator::NoiseGenerator(QObject *parent) :
	QObject(parent)
{
	m_noiseType = Noise::CONSTANT;
	m_noiseAmp = 0;
	m_noiseLvlPercent = 0;
	m_noiseGenerator = NULL;
}

NoiseGenerator::~NoiseGenerator()
{

}

void NoiseGenerator::SetNoiseType(Noise::NoiseType t_type)
{
	m_noiseType = t_type;
}

Noise::NoiseType NoiseGenerator::GetNoiseType()
{
	return m_noiseType;
}

void NoiseGenerator::SetNoiseAmplitude(const int &t_amp)
{
	m_noiseAmp = t_amp;
}

int NoiseGenerator::GetNoiseAmplitude()
{
	return m_noiseAmp;
}

void NoiseGenerator::SetNoiseLevel(const unsigned int &t_level)
{
	if ( 100 < t_level )
	{
		m_noiseLvlPercent = 100;
	}
	else
	{
		m_noiseLvlPercent = t_level;
	}
}

QImage NoiseGenerator::SetNoiseToImg(const QImage &t_img)
{
	switch(m_noiseType)
	{
		case Noise::CONSTANT:
//			break;
		case Noise::RANDOM:
//			break;
		case Noise::ABS_RANDOM:
		{
			m_noiseGenerator = new AbsRandNoise(t_img,
												m_noiseLvlPercent,
												m_noiseAmp,
												this);
			break;
		}
		default:
		{
			QImage sameImg = t_img;
			return sameImg;
		}
	}

	connect(m_noiseGenerator, SIGNAL(SignalProcProgressPrc(int)), this, SLOT(SlotGetProgressBarValue(int)));

	QImage noisedImg = m_noiseGenerator->GetNoisedImage();

	m_noiseGenerator->disconnect(SIGNAL(SignalProcProgressPrc(int)));

	delete m_noiseGenerator;

	if ( true == noisedImg.isNull() )
	{
		QImage sameImg = t_img;
		return sameImg;
	}

	return noisedImg;
}

void NoiseGenerator::SlotGetProgressBarValue(int t_progress)
{
	emit SignalProcProgressPrc(t_progress);
}
