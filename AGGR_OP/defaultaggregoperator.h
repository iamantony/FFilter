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

#ifndef DEFAULTAGGREGOPERATOR_H
#define DEFAULTAGGREGOPERATOR_H

#include <QObject>
#include <math.h>

class DefaultAggregOperator : public QObject
{
	Q_OBJECT
	// == DATA ==
protected:
	int m_result;

	// == METHODS ==
public:
	explicit DefaultAggregOperator(QObject *parent = 0);
	virtual int GetWorthlyValue(const QList<long double> &t_list) = 0;

protected:
	virtual void ResetValues() = 0;
	void CheckResult();
	void FormResult(const long double &t_result);
};

#endif // DEFAULTAGGREGOPERATOR_H
