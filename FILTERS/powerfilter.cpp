#include "powerfilter.h"

PowerFilter::PowerFilter(QObject *parent) :
	QObject(parent)
{
}

//QImage PowerFilter::FilterImg(QImage t_noisyImg, DefaultAggregOperator *t_aggrOp)
//{
//	if ( (true == t_noisyImg.isNull()) || (NULL == t_aggrOp) )
//	{
//		qDebug() << "FilterImg(): Error - invalid arguments";
//		return t_noisyImg;
//	}

//	QImage filteredImg = t_noisyImg;
//	int imgW = t_noisyImg.width();
//	int imgH = t_noisyImg.height();

//	int maskMinX = 0;
//	int maskMaxX = 0;
//	int maskMinY = 0;
//	int maskMaxY = 0;
//	const int maskOffset = 1;
//	const int lastPixelOnX = imgW - 1;
//	const int lastPixelOnY = imgH - 1;

//	QList<int> listOfPixels;
//	int resultLum = 0;
//	QColor pixel;
//	QRgb newPixel;

//	const int onePercent = imgW/100;
//	int progressPrc = 0;
//	int counter = 0;

//	// For each pixel in image
//	for (int w = 0; w < imgW; w++)
//	{
//		for (int h = 0; h < imgH; h++)
//		{
//			// Get list of pixels in mask
//			listOfPixels.clear();

//			maskMinX = qMax( (w - maskOffset), 0 );
//			maskMaxX = qMin( lastPixelOnX, (w + maskOffset) );
//			maskMinY = qMax( (h - maskOffset), 0 );
//			maskMaxY = qMin( lastPixelOnY, (h + maskOffset) );

//			for (int x = maskMinX; x <= maskMaxX; x++)
//			{
//				for (int y = maskMinY; y <= maskMaxY; y++)
//				{
//					pixel = t_noisyImg.pixel(x, y);
//					listOfPixels.append(pixel.red());
//				}
//			}

//			resultLum = t_aggrOp->GetWorthlyValue(listOfPixels);
//			if ( ERROR != resultLum )
//			{
//				newPixel = qRgb(resultLum, resultLum, resultLum);
//				filteredImg.setPixel(w, h, newPixel);
//			}
//		}

//		counter++;
//		if ( counter == onePercent )
//		{
//			counter = 0;
//			progressPrc++;
//			emit SignalProcProgressPrc(progressPrc);
//		}
//	}

//	return filteredImg;
//}

// TODO:
// 1. ImgHandler always have object of class PowerFilter.
// 2. Parameters from SettingsDialog and MaskWeightsDialog throw ImgHandler comes to PowerFilter.
// 3. Class AggOpHandler no longer needed
// 4. Mask structure:
// QList<MasksPixel> pixelsInMask
// struct MasksPixel
//{
//	int offsetX;
//	int offsetY;
//	double weight;
//};


// Get type of AggrOp and mask
void PowerFilter::Init()
{

}

// Public functions, that erform filtration
QImage PowerFilter::FilterImg(const QImage t_noisyImg)
{
	// For each pixel in image
	//	Get its coordinate and send them to method MaskFormer
	//	List from MaskFormer send to AggregOperator and get result luminance of reference pixel
	//	Change luminance of pixel
	// Return image
}

//
QList<double> PowerFilter::MaskFormer(const int &t_coordX, const int &t_coordY)
{
	// For each mask pixel in list pixelsInMask
	//	With given offset get luminance of masks pixel and multiply it with weight
	//	Add weighted pixel luminance to QList<double>
}
