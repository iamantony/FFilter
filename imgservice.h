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

#ifndef IMGSERVICE_H
#define IMGSERVICE_H

#include <QObject>
#include <QImage>
#include <QColor>
#include <time.h>
#include <math.h>
#include <QDebug>
#include "DEFINES/common.h"

#define MIN_SKO 0.00001

class ImgService : public QObject
{
	Q_OBJECT

	// == METHODS ==
public:
	explicit ImgService(QObject *parent = 0);

	QImage TransColorImgToGrayImg(const QImage &t_img);
	double CalcImgsSKO(const QImage &t_firstImg, const QImage &t_secondImg);

signals:
	void SignalProcProgressPrc(int t_progress);
};

#endif // IMGSERVICE_H
