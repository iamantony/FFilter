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

		return;
	}
}

ActiveMask* MaskStructure::GetMask()
{
	m_activeMask = new ActiveMask (FormActiveMask());
	return m_activeMask;
}

// Form list of only activated pixels in mask
QList<Mask::MasksPixel> MaskStructure::FormActiveMask()
{
	QList<Mask::MasksPixel> activeMask;

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
				activeMask.append(pixelsInLine->at(pixel));
			}
		}
	}

	return activeMask;
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
}

void MaskStructure::SlotFiltrationDone()
{
	delete m_activeMask;
}
