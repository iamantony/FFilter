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

#include "harmmeanaggregoperator.h"

HarmMeanAggregOperator::HarmMeanAggregOperator()
{
}

int HarmMeanAggregOperator::GetWorthlyValue(const QList<long double> &t_list)
{
	if ( true == t_list.isEmpty() )
	{
		qDebug() << "HarmMeanAggregOperator::GetWorthlyValue(): Error - list is empty!";
		return ERROR;
	}

	ResetValues();

	m_numOfValues = t_list.size();

	for (int i = 0; i < m_numOfValues; i++)
	{
		m_summ += 1/t_list.at(i);
	}

	m_summ *= (long double)1/m_numOfValues;
	m_summ = 1/m_summ;

	FormResult(m_summ);
	CheckResult();

	return m_result;
}

void HarmMeanAggregOperator::ResetValues()
{
	m_summ = 0;
	m_numOfValues = 0;
	m_result = 0;;
}
