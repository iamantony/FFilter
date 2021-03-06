#include "maxaggregoperator.h"

#include <algorithm>

#include <QDebug>

// Apply aggregation operator to list of values
// @input:
// - t_list - list of values
// @output:
// - int - result of operation
int MaxAggregOperator::Calc(const QList<double>& t_list)
{
    if ( t_list.isEmpty() )
    {
        qDebug() << __FUNCTION__ << "Error - invalid arguments";
        return 0;
    }

    QList<double>::const_iterator iter =
            std::max_element(t_list.constBegin(), t_list.constEnd());
    if ( iter == t_list.constEnd() )
    {
        qDebug() << __FUNCTION__ << "Failed to find max element";
        return 0;
    }

    return ResultToInt(*iter);
}
