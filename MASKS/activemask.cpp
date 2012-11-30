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

#include "activemask.h"

ActiveMask::ActiveMask(QList<Mask::MasksPixel> t_mask, QObject *parent) :
	QObject(parent)
{
	if ( true == t_mask.isEmpty() )
	{
		qDebug() << "ActiveMask(): Error - invalid arguments";
	}

	m_mask.clear();
	m_mask = t_mask;
}

// Get list of active pixel in mask for defined pixel from image t_img
QList<long double> ActiveMask::FormPixelMask(const QImage &t_img,
												const unsigned int &t_pixelCoordX,
												const unsigned int &t_pixelCoordY)
{
	if ( true == t_img.isNull() )
	{
		qDebug() << "ActiveMask::FormPixelMask(): Error - invalid arguments";
		QList<long double> emptyList;
		return emptyList;
	}

	QList<long double> pixelsInMask;

	for (int i = 0; i < m_mask.size(); i++)
	{
		m_maskPixelCoordX = t_pixelCoordX;
		m_maskPixelCoordY = t_pixelCoordY;

		if ( false == m_mask.at(i).isCentral )
		{
			m_maskPixelCoordX += m_mask.at(i).posX;
			m_maskPixelCoordY += m_mask.at(i).posY;
		}

		if ( false == t_img.valid(m_maskPixelCoordX, m_maskPixelCoordY) )
		{
			continue;
		}

		m_pixel = t_img.pixel(m_maskPixelCoordX, m_maskPixelCoordY);

		m_weightedPixel = m_mask.at(i).weight * (long double)m_pixel.red();

		pixelsInMask.append(m_weightedPixel);
	}

	return pixelsInMask;
}
