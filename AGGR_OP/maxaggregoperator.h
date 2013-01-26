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

#ifndef MAXAGGREGOPERATOR_H
#define MAXAGGREGOPERATOR_H

#include <math.h>
#include <QDebug>
#include "defaultaggregoperator.h"
#include "../DEFINES/common.h"
#include "../DEFINES/enums.h"

class MaxAggregOperator : public DefaultAggregOperator
{
	// == DATA ==
private:
	QList<long double> m_listOfValues;

	// == METHODS ==
public:
	MaxAggregOperator();
	int GetWorthlyValue(const QList<long double> &t_list);

protected:
	void ResetValues();
};

#endif // MAXAGGREGOPERATOR_H
