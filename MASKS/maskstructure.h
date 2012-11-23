#ifndef MASKSTRUCTURE_H
#define MASKSTRUCTURE_H

#include <QObject>
#include <QMessageBox>
#include <QMap>
#include <QImage>
#include <QColor>
#include <QDebug>
#include "../DEFINES/common.h"
#include "../DEFINES/mask.h"

class MaskStructure : public QObject
{
	Q_OBJECT

	// == DATA ==
private:
	unsigned int m_rowsInMask;
	unsigned int m_columsInMask;
	QMap<unsigned int, QList<Mask::MasksPixel> > m_mask;
	QList<Mask::MasksPixel> m_activeMask;
	QColor m_pixel;
	long double m_weightedPixel;
	int m_maskPixelCoordX;
	int m_maskPixelCoordY;

	// == METHODS ==
public:
	explicit MaskStructure(QObject *parent = 0);
	// Get list of pixel in mask for defined pixel from image t_img
	QList<long double> FormPixelMask(const QImage &t_img,
									 const unsigned int &t_pixelCoordX,
									 const unsigned int &t_pixelCoordY);

	// Send current mask
	QMap<unsigned int, QList<Mask::MasksPixel> > GetMaskStructure();
	// Set new mask structure
	void SetMaskStructure(QMap<unsigned int, QList<Mask::MasksPixel> > t_mask);

private:
	void SetMaskSize();
	void SetDefaultMask();
	// Form list of only activated pixels in mask
	void FormActiveMask();
	// Check if mask structure is valid
	bool CheckMask(QMap<unsigned int, QList<Mask::MasksPixel> > t_mask);
};

#endif // MASKSTRUCTURE_H
