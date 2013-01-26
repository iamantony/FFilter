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
 *	along with FFilter. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEFAULTNOISE_H
#define DEFAULTNOISE_H

#include <QObject>
#include <QImage>
#include <time.h>
#include <QDebug>

class DefaultNoise : public QObject
{
	Q_OBJECT
	// == DATA ==
protected:
	QImage m_imgToNoise;
	int m_noiseAmplitude;
	unsigned int m_noiseLevelPercent;
	unsigned int m_pixelsToNoise;
	unsigned int m_numPixToChange;
	bool m_needToNoise;
	bool **m_pixelsToChange;

	// == METHODS ==
public:
	explicit DefaultNoise(const QImage &t_img,
						  const unsigned int &t_noiseLvl = 0,
						  const int &t_noiseAmp = 0,
						  QObject *parent = 0);

	~DefaultNoise();

	virtual QImage GetNoisedImage() = 0;

protected:
	virtual QList<int> GenerateNoise() = 0;

private:
	void CreateImgNoiseMap();

signals:
	void SignalProcProgressPrc(int t_progress);
};

#endif // DEFAULTNOISE_H
