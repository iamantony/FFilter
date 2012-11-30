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

#include "imgservice.h"

ImgService::ImgService(QObject *parent) :
	QObject(parent)
{
}

QImage ImgService::TransColorImgToGrayImg(const QImage &t_img)
{
	if ( true == t_img.isNull() )
	{
		qDebug() << "TransColorImgToGrayImg(): Error - invalid arguments";
		QImage nullImg;
		return nullImg;
	}

	int width = t_img.width();
	int height = t_img.height();
	QImage grayImg(width, height, QImage::Format_RGB32);

	QColor pixel;
	int resultLuminance;
	double grayPixel;

	int onePercent = width/100;
	int progressPrc = 0;
	int counter = 0;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			pixel = t_img.pixel(x, y);
			grayPixel = 0.2126 * pixel.red() + 0.7152 * pixel.green() + 0.0722 * pixel.blue();
			resultLuminance = (int)floor(grayPixel + 0.5);

			if( resultLuminance < 0 )
			{
				resultLuminance = 0;
			}
			else if( resultLuminance > 255 )
			{
				resultLuminance = 255;
			}

			pixel.setRed(resultLuminance);
			pixel.setGreen(resultLuminance);
			pixel.setBlue(resultLuminance);

			grayImg.setPixel(x, y, pixel.rgb());
		}

		// Count progress of operation in percent
		counter++;
		if ( counter == onePercent )
		{
			counter = 0;
			progressPrc++;
			// Change value of ProgressBar on MainWindow
			emit SignalProcProgressPrc(progressPrc);
		}
	}

	return grayImg;
}

double ImgService::CalcImgsSKO(const QImage &t_firstImg, const QImage &t_secondImg)
{
	int firstW = t_firstImg.width();
	int firstH = t_firstImg.height();
	int secondW = t_secondImg.width();
	int secondH = t_secondImg.height();

	// Our images have the same size?
	if ( (firstW != secondW) || (firstH != secondH) )
	{
		return ERROR;
	}

	QColor pixelFirst;
	QColor pixelSecond;
	double SKO = 0.0;
	int rFirst, rSecond, diffRed;
	int gFirst, gSecond, diffGreen;
	int bFirst, bSecond, diffBlue;

	int onePercent = ( firstW * firstH )/100;
	int progressPrc = 0;
	int counter = 0;

	for (int x = 0; x < firstW; x++)
	{
		for (int y = 0; y < firstH; y++)
		{
			pixelFirst = t_firstImg.pixel(x, y);
			pixelSecond = t_secondImg.pixel(x, y);

			// get square of difference between red channels of images
			rFirst = pixelFirst.red();
			rSecond = pixelSecond.red();
			diffRed = pow( (rFirst - rSecond), 2 );

			// get square of difference between green channels of images
			gFirst = pixelFirst.green();
			gSecond = pixelSecond.green();
			diffGreen = pow( (gFirst - gSecond), 2);

			// get square of difference between blue channels of images
			bFirst = pixelFirst.blue();
			bSecond = pixelSecond.blue();
			diffBlue = pow( (bFirst - bSecond), 2);

			// sum all squares
			SKO += diffRed + diffGreen + diffBlue;

			counter++;
			if ( counter == onePercent )
			{
				counter = 0;
				progressPrc++;
				emit SignalProcProgressPrc(progressPrc);
			}
		}
	}

	// get mean of square SKO for each pixel
	SKO = SKO /( firstW * firstH );
	if (SKO < MIN_SKO)
	{
		SKO = 0;
	}
	else
	{
		// get root
		SKO = pow(SKO, 0.5);
	}

	return SKO;
}
