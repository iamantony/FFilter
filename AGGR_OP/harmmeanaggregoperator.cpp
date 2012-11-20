#include "harmmeanaggregoperator.h"

HarmMeanAggregOperator::HarmMeanAggregOperator()
{
}

int HarmMeanAggregOperator::GetWorthlyValue(const QList<int> &t_list)
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
		m_summ += (long double)1/t_list.at(i);
	}

	m_summ *= (long double)1/m_numOfValues;
	m_summ = 1/m_summ;

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

void HarmMeanAggregOperator::ResetValues()
{
	m_summ = 0;
	m_numOfValues = 0;
	m_result = 0;;
}
