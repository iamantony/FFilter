#include "maxaggregoperator.h"

MaxAggregOperator::MaxAggregOperator()
{
}

int MaxAggregOperator::GetWorthlyValue(const QList<int> &t_list)
{
	if ( true == t_list.isEmpty() )
	{
		qDebug() << "MaxAggregOperator::GetWorthlyValue(): Error - list is empty!";
		return ERROR;
	}

	ResetValues();

	m_listOfValues = t_list;
	qSort(m_listOfValues);

	return m_listOfValues.last();
}

void MaxAggregOperator::ResetValues()
{
	m_listOfValues.clear();
}
