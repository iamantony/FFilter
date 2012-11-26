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
		QList<Mask::MasksPixel> newLine;

		for( unsigned int y = 0; y < m_columsInMask; y++ )
		{
			Mask::MasksPixel pixel;

			if ( (x == centralPixelX) && (y == centralPixelY) )
			{
				pixel.isEnabled = true;
				pixel.isCentral = true;
				pixel.posX = centralPixelX;
				pixel.posY = centralPixelY;
				pixel.weight = 1;
			}
			else
			{
				pixel.isEnabled = false;
				pixel.isCentral = false;
				pixel.posX = x - centralPixelX;
				pixel.posY = y - centralPixelY;
				pixel.weight = 0;
			}

			newLine.append(pixel);
		}

		m_mask.insert(x, newLine);
	}

	bool maskIsGood = CheckMask(m_mask);
	if ( false == maskIsGood )
	{
		qDebug() << "MaskStructure::SetDefaultMask(): Critical error - can't form proper default mask";

		m_mask.clear();
		m_activeMask.clear();

		return;
	}

	FormActiveMask();
}

// Form list of only activated pixels in mask
void MaskStructure::FormActiveMask()
{
	m_activeMask.clear();

	// Get list of all keys in full mask
	QList<unsigned int> linesInMask = m_mask.keys();

	// For all lines in mask
	for (int line = 0; line < linesInMask.size(); line++)
	{
		// Get all pixels in line
		QList<Mask::MasksPixel> *pixelsInLine = &m_mask[linesInMask.at(line)];
		for (int pixel = 0; pixel < pixelsInLine->size(); pixel++)
		{
			// And add to list only active (enabled) pixels
			if ( true == pixelsInLine->at(pixel).isEnabled )
			{
				m_activeMask.append(pixelsInLine->at(pixel));
			}
		}
	}
}

// Check if mask structure is valid
bool MaskStructure::CheckMask(QMap<unsigned int, QList<Mask::MasksPixel> > t_mask)
{
	// See Mask Rules in mask defines (DEFINES/mask.h)

	unsigned int numOfCentralPixels = 0;
	unsigned int numOfActivePixels = 0;

	QList<Mask::MasksPixel> allPixels;
	QList<unsigned int> lines = t_mask.keys();
	for (int i = 0; i < lines.size(); i++)
	{
		unsigned int key = lines.at(i);
		allPixels.append(t_mask.value(key));
	}

	// Get statistic
	for (int pix = 0; pix < allPixels.size(); pix++)
	{
		if ( true == allPixels.at(pix).isCentral )
		{
			numOfCentralPixels++;
		}

		if ( true == allPixels.at(pix).isEnabled )
		{
			numOfActivePixels++;
		}
	}

	// Check the Rules:
	if ( NUM_OF_CENTRAL_PIXELS != numOfCentralPixels )
	{
		qDebug() << "MaskStructure::CheckMask(): Rule of number of central pixels in mask doesn't hold";
//		QMessageBox::warning(this, "Filter Mask Error", "Mask must have only one central pixel. Default mask set");
		return false;
	}

	if ( numOfActivePixels < MIN_NUM_OF_ACTIVE_PIXELS )
	{
		qDebug() << "MaskStructure::CheckMask(): Rule of minimum number of active pixels in mask doesn't hold";
//		QMessageBox::warning(this, "Filter Mask Error", "Mask must have at least one active pixel. Default mask set");
		return false;
	}

	// TODO: send warning signal to main window

	return true;
}

// Get list of active pixel in mask for defined pixel from image t_img
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

	for (int i = 0; i < m_activeMask.size(); i++)
	{
		m_maskPixelCoordX = t_pixelCoordX;
		m_maskPixelCoordY = t_pixelCoordY;

		if ( false == m_activeMask.at(i).isCentral )
		{
			m_maskPixelCoordX += m_activeMask.at(i).posX;
			m_maskPixelCoordY += m_activeMask.at(i).posY;
		}

		if ( false == t_img.valid(m_maskPixelCoordX, m_maskPixelCoordY) )
		{
			continue;
		}

		m_pixel = t_img.pixel(m_maskPixelCoordX, m_maskPixelCoordY);

		m_weightedPixel = m_activeMask.at(i).weight * (long double)m_pixel.red();

		pixelsInMask.append(m_weightedPixel);
	}

	return pixelsInMask;
}

// Send current mask
QMap<unsigned int, QList<Mask::MasksPixel> > MaskStructure::GetMaskStructure()
{
	return m_mask;
}

// Set new mask structure
void MaskStructure::SetMaskStructure(QMap<unsigned int, QList<Mask::MasksPixel> > t_mask)
{
	if ( true == t_mask.isEmpty() )
	{
		qDebug() << "MaskStructure::SlotSetMaskStructure(): Error - mask is empty. Default mask set.";
		SetDefaultMask();
	}

	bool newMaskIsGood = CheckMask(t_mask);
	if ( false == newMaskIsGood )
	{
		qDebug() << "MaskStructure::SlotSetMaskStructure(): Error - new mask is not math ther Mask Rules";
		return;
	}

	m_mask.clear();
	m_mask = t_mask;

	FormActiveMask();
}
