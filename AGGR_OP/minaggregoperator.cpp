#include "minaggregoperator.h"

MinAggregOperator::MinAggregOperator()
{
}

int MinAggregOperator::GetWorthlyValue(const QList<int> &t_list)
{
	if ( true == t_list.isEmpty() )
	{
		qDebug() << "MinAggregOperator::GetWorthlyValue(): Error - list is empty!";
		return ERROR;
	}

	ResetValues();

	m_listOfValues = t_list;
	qSort(m_listOfValues);

	return m_listOfValues.first();
}

void MinAggregOperator::ResetValues()
{
	m_listOfValues.clear();
}
