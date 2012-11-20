#include "medaggregoperator.h"

MedAggregOperator::MedAggregOperator()
{
}

int MedAggregOperator::GetWorthlyValue(const QList<int> &t_list, int t_position)
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
		m_result += m_listOfValues.at(m_mean - 1);
		m_result += m_listOfValues.at(m_mean);
		m_result /= 2;
	}
	else
	{
		// m_numOfValues is an odd number
		m_result = m_listOfValues.at(m_mean);
	}

	if ( m_result < 0 )
	{
		m_result = 0;
	}
	else if ( 255 < m_result )
	{
		m_result = 255;
	}

	return m_result;
}

void MedAggregOperator::ResetValues()
{
	m_listOfValues.clear();
	m_numOfValues = 0;
	m_mean = 0;
	m_modulo = 0;
	m_result = 0;
}
