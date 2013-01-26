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

#ifndef ACTIVEMASK_H
#define ACTIVEMASK_H

#include <QObject>
#include <QList>
#include <QImage>
#include <QColor>
#include <QDebug>
#include "activemask.h"
#include "../DEFINES/common.h"
#include "../DEFINES/mask.h"

class ActiveMask : public QObject
{
	Q_OBJECT

	// == DATA ==
private:
	QList<Mask::MasksPixel> m_mask;
	QColor m_pixel;
	long double m_weightedPixel;
	int m_maskPixelCoordX;
	int m_maskPixelCoordY;

	// == METHODS ==
public:
	explicit ActiveMask( QList<Mask::MasksPixel> t_mask, QObject *parent = 0);

	// Get list of active pixel in mask for defined pixel from image t_img
	QList<long double> FormPixelMask(const QImage &t_img,
									 const unsigned int &t_pixelCoordX,
									 const unsigned int &t_pixelCoordY);


};

#endif // ACTIVEMASK_H
