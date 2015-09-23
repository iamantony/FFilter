#include "maxaggregoperator.h"

#include <algorithm>

#include <QDebug>

int MaxAggregOperator::GetWorthyValue(const QList<long double>& t_list)
{
    if ( true == t_list.isEmpty() )
    {
        qDebug() << __FUNCTION__ << "Error - invalid arguments";
        return 0;
    }

    QList<long double>::const_iterator iter =
            std::max_element(t_list.constBegin(), t_list.constEnd());
    if ( iter == t_list.constEnd() )
    {
        qDebug() << __FUNCTION__ << "Failed to find max element";
        return 0;
    }

    ResetValues();
    FormResult(*iter);
    CheckResult();

    return m_result;
}
