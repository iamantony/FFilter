#include "minaggregoperator.h"

#include "common/common.h"

MinAggregOperator::MinAggregOperator()
{
}

int MinAggregOperator::GetWorthyValue(const QList<long double> &t_list)
{
    if ( true == t_list.isEmpty() )
    {
        qDebug() << "MinAggregOperator::GetWorthlyValue(): Error - list is empty!";
        return ERROR;
    }

    ResetValues();

    m_listOfValues = t_list;
    qSort(m_listOfValues);

    FormResult(m_listOfValues.first());
    CheckResult();

    return m_result;
}

void MinAggregOperator::ResetValues()
{
    m_listOfValues.clear();
    m_result = 0;
}
