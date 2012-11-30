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

#ifndef ABSRANDNOISE_H
#define ABSRANDNOISE_H

#include <time.h>
#include <QImage>
#include <QDebug>
#include "defaultnoise.h"

class AbsRandNoise : public DefaultNoise
{
	// == METHODS ==
public:
	AbsRandNoise(const QImage &t_img,
				 const unsigned int &t_noiseLvl = 0,
				 const int &t_noiseAmp = 0,
				 QObject *parent = 0):
		DefaultNoise(t_img, t_noiseLvl, t_noiseAmp, parent)
	{}

	QImage GetNoisedImage();

protected:
	QList<int> GenerateNoise();
};

#endif // ABSRANDNOISE_H
