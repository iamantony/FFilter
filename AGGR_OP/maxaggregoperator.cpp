#include "maxaggregoperator.h"

MaxAggregOperator::MaxAggregOperator()
{
}

int MaxAggregOperator::GetWorthlyValue(const QList<long double> &t_list)
{
	if ( true == t_list.isEmpty() )
	{
		qDebug() << "MaxAggregOperator::GetWorthlyValue(): Error - list is empty!";
		return ERROR;
	}

	ResetValues();

	m_listOfValues = t_list;
	qSort(m_listOfValues);

	m_result = (int)floor(m_listOfValues.last() + 0.5);
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

void MaxAggregOperator::ResetValues()
{
	m_listOfValues.clear();
	m_result = 0;
}
