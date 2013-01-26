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
 *	along with FFilter. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef POWERFILTER_H
#define POWERFILTER_H

#include <QObject>
#include <QImage>
#include <QColor>
#include <QDebug>
#include "MASKS/activemask.h"
#include "AGGR_OP/defaultaggregoperator.h"
#include "DEFINES/common.h"

class PowerFilter : public QObject
{
	Q_OBJECT

	// == DATA ==
private:
	ActiveMask *m_mask;
	DefaultAggregOperator *m_aggregOperator;

	// == METHODS ==
public:
	explicit PowerFilter(QObject *parent = 0);
	~PowerFilter();

	void Init(ActiveMask *t_mask, DefaultAggregOperator *t_aggrOp);
	QImage FilterImg(const QImage &t_noisyImg);

private:
	void SetDefaults();

signals:
	void SignalProcProgressPrc(int t_progress);
	void SignalFiltrationFinished();
};

#endif // POWERFILTER_H
