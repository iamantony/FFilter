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

#include "medaggregoperator.h"

MedAggregOperator::MedAggregOperator()
{
}

int MedAggregOperator::GetWorthlyValue(const QList<long double> &t_list)
{
	if ( true == t_list.isEmpty() )
	{
		qDebug() << "MedAggregOperator::GetWorthlyValue(): Error - list is empty!";
		return ERROR;
	}

	ResetValues();

	m_listOfValues = t_list;
	qSort(m_listOfValues);

	m_numOfValues = m_listOfValues.size();
	m_mean = (m_numOfValues / 2);
	m_modulo = m_numOfValues % 2;
	if ( 0 == m_modulo )
	{
		// m_numOfValues is an even number
		m_summ += m_listOfValues.at(m_mean - 1);
		m_summ += m_listOfValues.at(m_mean);
		m_summ /= 2;
	}
	else
	{
		// m_numOfValues is an odd number
		m_summ = m_listOfValues.at(m_mean);
	}

	FormResult(m_summ);
	CheckResult();

	return m_result;
}

void MedAggregOperator::ResetValues()
{
	m_listOfValues.clear();
	m_numOfValues = 0;
	m_mean = 0;
	m_modulo = 0;
	m_summ = 0;
	m_result = 0;
}
