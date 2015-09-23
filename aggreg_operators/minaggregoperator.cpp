#include "minaggregoperator.h"

#include <algorithm>

#include <QDebug>

int MinAggregOperator::GetWorthyValue(const QList<double>& t_list)
{
    if ( true == t_list.isEmpty() )
    {
        qDebug() << __FUNCTION__ << "Error - list is empty";
        return 0;
    }

    QList<double>::const_iterator iter =
            std::min_element(t_list.constBegin(), t_list.constEnd());
    if ( iter == t_list.constEnd() )
    {
        qDebug() << __FUNCTION__ << "Failed to find min element";
        return 0;
    }

    ResetValues();
    FormResult(*iter);
    CheckResult();

    return m_result;
}
