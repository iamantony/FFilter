#ifndef MASKSTRUCTURE_H
#define MASKSTRUCTURE_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QImage>
#include <QColor>
#include <QDebug>
#include "activemask.h"
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
	ActiveMask *m_activeMask;

	// == METHODS ==
public:
	explicit MaskStructure(QObject *parent = 0);

	// Send current mask
	QMap<unsigned int, QList<Mask::MasksPixel> > GetMaskStructure();
	// Set new mask structure
	void SetMaskStructure(QMap<unsigned int, QList<Mask::MasksPixel> > t_mask);
	ActiveMask *GetMask();

private:
	void SetMaskSize();
	void SetDefaultMask();
	// Form list of only activated pixels in mask
	QList<Mask::MasksPixel> FormActiveMask();
	// Check if mask structure is valid
	bool CheckMask(QMap<unsigned int, QList<Mask::MasksPixel> > t_mask);

public slots:
	void SlotFiltrationDone();
};

#endif // MASKSTRUCTURE_H
