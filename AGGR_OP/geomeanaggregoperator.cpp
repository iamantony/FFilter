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

#include "geomeanaggregoperator.h"

GeoMeanAggregOperator::GeoMeanAggregOperator()
{
}

int GeoMeanAggregOperator::GetWorthlyValue(const QList<long double> &t_list)
{
	if ( true == t_list.isEmpty() )
	{
		qDebug() << "GeoMeanAggregOperator::GetWorthlyValue(): Error - list is empty!";
		return ERROR;
	}

	ResetValues();

	m_numOfValues = t_list.size();

	// Lets find in list first non-null value
	for (int val = 0; val < m_numOfValues; val++)
	{
		if ( 0 < t_list.at(val) )
		{
			m_product = t_list.at(val);
			m_startValue = val + 1;
			break;
		}
	}

	if ( 0 == m_product )
	{
		// If all values in list are 0, our answer will be 0 too.
		m_rootedProduct = 0;
	}
	else
	{
		// If in list we've found non-zero value, lets calculate product of all non-zero values in list
		for (int val = m_startValue; val < m_numOfValues; val++)
		{
			if ( 0 < t_list.at(val) )
			{
				m_product *= t_list.at(val);
			}
		}

		// Get root of product
		m_power = 1/(long double)m_numOfValues;
		m_rootedProduct = pow(m_product, m_power);
	}

	FormResult(m_rootedProduct);
	CheckResult();

	return m_result;
}

void GeoMeanAggregOperator::ResetValues()
{
	m_product = 0;
	m_numOfValues = 0;
	m_startValue = 0;
	m_rootedProduct = 0;
	m_power = 1;
	m_result = 0;
}
