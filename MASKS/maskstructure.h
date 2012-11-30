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
