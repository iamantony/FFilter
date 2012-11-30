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

#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H

#include <QObject>
#include <QImage>
#include <QDebug>
#include "defaultnoise.h"
#include "constnoise.h"
#include "randnoise.h"
#include "absrandnoise.h"
#include "DEFINES/common.h"
#include "DEFINES/enums.h"

class NoiseGenerator : public QObject
{
	Q_OBJECT

	// == DATA ==
private:
	Noise::NoiseType m_noiseType;
	int m_noiseAmp;
	unsigned int m_noiseLvlPercent;
	DefaultNoise *m_noiseGenerator;

	// == METHODS ==
public:
	explicit NoiseGenerator(QObject *parent = 0);
	~NoiseGenerator();

	void SetNoiseType(Noise::NoiseType t_type);
	Noise::NoiseType GetNoiseType();
	void SetNoiseAmplitude(const int &t_amp);
	int GetNoiseAmplitude();
	void SetNoiseLevel(const unsigned int &t_level);
	QImage SetNoiseToImg(const QImage &t_img);

signals:
	void SignalProcProgressPrc(int t_progress);

public slots:
	void SlotGetProgressBarValue(int t_progress);
};

#endif // NOISEGENERATOR_H
