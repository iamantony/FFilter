/* === This file is part of FFilter ===
 *
 *	Copyright 2012, Antony Cherepanov <antony.cherepanov@gmail.com>
 *
 *	FFilter is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	FFilter is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

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
		{
			m_noiseGenerator = new ConstNoise(t_img,
											  m_noiseLvlPercent,
											  m_noiseAmp,
											  this);

			break;
		}
		case Noise::RANDOM:
		{
			m_noiseGenerator = new RandNoise(t_img,
											 m_noiseLvlPercent,
											 m_noiseAmp,
											 this);

			break;
		}
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
