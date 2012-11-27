#include "noisegenerator.h"

NoiseGenerator::NoiseGenerator(QObject *parent) :
	QObject(parent)
{
	m_noiseType = Noise::CONSTANT;
	m_noiseAmp = 0;
	m_noiseLvlPercent = 0;
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
