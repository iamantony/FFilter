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

	FormResult(m_listOfValues.last());
	CheckResult();

	return m_result;
}

void MaxAggregOperator::ResetValues()
{
	m_listOfValues.clear();
	m_result = 0;
}
