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

#include "powerfilter.h"

PowerFilter::PowerFilter(QObject *parent) :
	QObject(parent)
{
	SetDefaults();
}

PowerFilter::~PowerFilter()
{
	SetDefaults();
}

void PowerFilter::SetDefaults()
{
	m_mask = NULL;
	m_aggregOperator = NULL;
}

void PowerFilter::Init(ActiveMask *t_mask, DefaultAggregOperator *t_aggrOp)
{
	if ( (NULL == t_mask) || (NULL == t_aggrOp) )
	{
		qDebug() << "PowerFilter::Init(): Error - invalid arguments";
		return;
	}

	m_mask = t_mask;
	m_aggregOperator = t_aggrOp;
}

QImage PowerFilter::FilterImg(const QImage &t_noisyImg)
{
	if ( (NULL == m_mask) || (NULL == m_aggregOperator) )
	{
		qDebug() << "PowerFilter::FilterImg(): Error - filter is not initialised";
		return t_noisyImg;
	}

	if ( true == t_noisyImg.isNull() )
	{
		qDebug() << "PowerFilter::FilterImg(): Error - invalid arguments";
		return t_noisyImg;
	}

	QImage filteredImg = t_noisyImg;
	unsigned int imgW = (unsigned int)t_noisyImg.width();
	unsigned int imgH = (unsigned int)t_noisyImg.height();

	QList<long double> pixelsInMask;
	int resultLum = 0;
	QRgb newPixel;

	const int onePercent = imgW/100;
	int progressPrc = 0;
	int counter = 0;

	// For each pixel in image
	for (unsigned int w = 0; w < imgW; w++)
	{
		for (unsigned int h = 0; h < imgH; h++)
		{
			// Get list of pixels in mask
			pixelsInMask.clear();
			pixelsInMask = m_mask->FormPixelMask(t_noisyImg, w, h);
			resultLum = m_aggregOperator->GetWorthlyValue(pixelsInMask);
			if ( ERROR != resultLum )
			{
				newPixel = qRgb(resultLum, resultLum, resultLum);
				filteredImg.setPixel(w, h, newPixel);
			}
		}

		counter++;
		if ( counter == onePercent )
		{
			counter = 0;
			progressPrc++;
			emit SignalProcProgressPrc(progressPrc);
		}
	}

	emit SignalFiltrationFinished();

	return filteredImg;
}
