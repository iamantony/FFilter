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

#include "defaultaggregoperator.h"

DefaultAggregOperator::DefaultAggregOperator(QObject *parent) :
	QObject(parent)
{
}

void DefaultAggregOperator::CheckResult()
{
	if ( m_result < 0 )
	{
		m_result = 0;
	}
	else if ( 255 < m_result )
	{
		m_result = 255;
	}
}

void DefaultAggregOperator::FormResult(const long double &t_result)
{
	m_result = (int)floor(t_result + 0.5);
}
