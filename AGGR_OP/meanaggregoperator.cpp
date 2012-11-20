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

int MeanAggregOperator::GetWorthlyValue(const QList<int> &t_list)
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

	m_result = (int)floor(m_summ + 0.5);
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

void MeanAggregOperator::ResetValues()
{
	m_summ = 0;
	m_numOfValues = 0;
	m_result = 0;
}
