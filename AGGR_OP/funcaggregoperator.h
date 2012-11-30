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

#ifndef FUNCAGGREGOPERATOR_H
#define FUNCAGGREGOPERATOR_H

#include <math.h>
#include <QList>
#include <QDebug>
#include "defaultaggregoperator.h"
#include "../DEFINES/common.h"
#include "../DEFINES/enums.h"

class FuncAggregOperator : public DefaultAggregOperator
{
	// == DATA ==
private:
	long double (*m_directFunc) (long double);
	long double (*m_inverseFunc) (long double);
	int m_numOfValues;
	long double m_summ;

	// == METHODS ==
public:
	FuncAggregOperator(AggregOperatorFunc::AggrOpFunc t_func);
	int GetWorthlyValue(const QList<long double> &t_list);

protected:
	void ResetValues();
};

#endif // FUNCAGGREGOPERATOR_H
