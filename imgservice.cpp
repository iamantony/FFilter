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
			grayPixel = 0.299 * pixel.red() + 0.587 * pixel.green() + 0.114 * pixel.blue();
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

QImage ImgService::SetNoiseToImg(const QImage &img, const unsigned int &t_noiseLvl)
{
	if ( (true == img.isNull()) || (100 < t_noiseLvl))
	{
		qDebug() << "SetNoiseToImg(): Error - invalid arguments";
		QImage nullImg;
		return nullImg;
	}

	QImage noisyImg = img;

	// What the point of adding zero noise?
	if ( 0 == t_noiseLvl )
	{
		return noisyImg;
	}

	srand(time(NULL));

	int noiseLvl = t_noiseLvl;
	bool needToNoise = true;

	// If noiseLvl > 50% we invert an algorith. What does it mean? Well, in usual way (noiseLvl < 50%) we choose
	// noiseLvl% of pixels and add noise to them. But when noiseLvl > 50% this algorithm is quite slow. It's easier
	// to choose noiseLvl% of pixels and DON'T noise them.
	if ( 50 < noiseLvl )
	{
		noiseLvl = 100 - noiseLvl;
		needToNoise = false;
	}

	int imgW = noisyImg.width();
	int imgH = noisyImg.height();
	int pixelsToNoise = ( noiseLvl * imgW * imgH ) / 100;
	int wRand = 0;
	int hRand = 0;

	// This bool mass help us to noise pixels only once.
	bool **pixelsNoised = new bool* [imgW];
	for ( int pix = 0; pix < imgW; pix++ )
	{
		pixelsNoised[pix] = new bool [imgH];
	}

	// Set default value
	for ( int w = 0; w < imgW; w++ )
	{
		for ( int h = 0; h < imgH; h++ )
		{
			pixelsNoised[w][h] = false;
		}
	}

	// Then by random we choose pixels and define their fate:
	// - if noiseLvl < 50%, then they will be noised
	// - if noiseLvl > 50%, then they value will be saved (and unchoosed will be noised)
	for ( int pix = 0; pix < pixelsToNoise; pix++ )
	{
		do
		{
			wRand = rand() % imgW;
			hRand = rand() % imgH;
			if ( false == pixelsNoised[wRand][hRand] )
			{
				pixelsNoised[wRand][hRand] = true;
				break;
			}
		}
		while( 1 );
	}

	int pixelLum = 0;
	QRgb pixel;

	int onePercent = pixelsToNoise/100;
	int progressPrc = 0;
	int counter = 0;

	// Start algorith
	for ( int w = 0; w < imgW; w++ )
	{
		for ( int h = 0; h < imgH; h++ )
		{
			pixelLum = rand() % 256;
			pixel = qRgb(pixelLum, pixelLum, pixelLum);

			if ( needToNoise == pixelsNoised[w][h] )
			{
				noisyImg.setPixel(w, h, pixel);
			}

			counter++;
			if ( counter == onePercent )
			{
				counter = 0;
				progressPrc++;
				emit SignalProcProgressPrc(progressPrc);
			}
		}
	}

	for (int line = 0; line < imgW; line++)
	{
		delete [] pixelsNoised[line];
	}

	delete [] pixelsNoised;

	return noisyImg;
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
