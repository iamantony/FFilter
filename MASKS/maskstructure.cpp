#include "maskstructure.h"

MaskStructure::MaskStructure(QObject *parent) :
	QObject(parent)
{
	SetMaskSize();
	SetDefaultMask();
}

void MaskStructure::SetMaskSize()
{
	if ( ROWS_IN_MASK <= 0 )
	{
		m_rowsInMask = 1;
	}
	else
	{
		m_rowsInMask = ROWS_IN_MASK;
	}

	if ( COLUMS_IN_MASK <= 0 )
	{
		m_columsInMask = 1;
	}
	else
	{
		m_columsInMask = COLUMS_IN_MASK;
	}
}

void MaskStructure::SetDefaultMask()
{
	unsigned int centralPixelX = m_rowsInMask/2;
	unsigned int centralPixelY = m_columsInMask/2;

	m_mask.clear();

	for( unsigned int x = 0; x < m_rowsInMask; x++ )
	{
		for( unsigned int y = 0; y < m_columsInMask; y++ )
		{
			Mask::MasksPixel pixel;

			if ( (x == centralPixelX) && (y == centralPixelY) )
			{
				pixel.isEnabled = true;
				pixel.isCentral = true;
			}
			else
			{
				pixel.isEnabled = false;
				pixel.isCentral = false;
			}

			pixel.offsetX = x - centralPixelX;
			pixel.offsetY = y - centralPixelY;
			pixel.weight = 1;

			m_mask.append(pixel);
		}
	}
}

// Get list of pixel in mask for defined pixel from image t_img
QList<long double> MaskStructure::FormPixelMask(const QImage &t_img,
												const unsigned int &t_pixelCoordX,
												const unsigned int &t_pixelCoordY)
{
	if ( true == t_img.isNull() )
	{
		qDebug() << "MaskStructure::FormPixelMask(): Error - invalid arguments";
		QList<long double> emptyList;
		return emptyList;
	}

	QList<long double> pixelsInMask;

	for (int i = 0; i < m_mask.size(); i++)
	{
		if ( false == m_mask.at(i).isEnabled )
		{
			continue;
		}

		m_maskPixelCoordX = t_pixelCoordX + m_mask.at(i).offsetX;
		m_maskPixelCoordY = t_pixelCoordY + m_mask.at(i).offsetY;

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

// Set new mask structure
void MaskStructure::SlotSetMaskStructure(QList<Mask::MasksPixel> t_mask)
{
	if ( true == t_mask.isEmpty() )
	{
		qDebug() << "MaskStructure::SlotSetMaskStructure(): Error - mask is empty. Default mask set.";
		SetDefaultMask();
	}

	m_mask.clear();
	m_mask = t_mask;
}
