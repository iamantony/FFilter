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

#include "meanaggregoperator.h"

MeanAggregOperator::MeanAggregOperator(const double &t_power)
{
	if ( 0 == t_power )
	{
		m_power = 1;
	}
	else
	{
		m_power = (long double)t_power;
	}
}

int MeanAggregOperator::GetWorthlyValue(const QList<long double> &t_list)
{
	if ( true == t_list.isEmpty() )
	{
		qDebug() << "MaxAggregOperator::GetWorthlyValue(): Error - list is empty!";
		return ERROR;
	}

	ResetValues();

	m_numOfValues = t_list.size();

	for (int i = 0; i < m_numOfValues; i++)
	{
		if ( 0 < t_list.at(i) )
		{
			m_summ += pow(t_list.at(i), m_power);
		}
	}

	m_summ /= (long double)m_numOfValues;
	m_summ = pow( m_summ, (1/m_power) );

	FormResult(m_summ);
	CheckResult();

	return m_result;
}

void MeanAggregOperator::ResetValues()
{
	m_summ = 0;
	m_numOfValues = 0;
	m_result = 0;
}
