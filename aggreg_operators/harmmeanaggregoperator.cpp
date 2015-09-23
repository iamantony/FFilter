#include "harmmeanaggregoperator.h"

#include <limits>

#include <QDebug>

// Apply aggregation operator to list of values
// @input:
// - t_list - list of values
// @output:
// - int - result of operation
int HarmMeanAggregOperator::Calc(const QList<double>& t_list)
{
    if ( t_list.isEmpty() )
    {
        qDebug() << __FUNCTION__ << "Error - list is empty";
        return 0;
    }

    double summ = 0.0;
    for (int i = 0; i < t_list.size(); ++i)
    {
        if ( std::numeric_limits<double>::epsilon() < std::abs(t_list.at(i)) )
        {
            summ += 1 / t_list.at(i);
        }
    }

    summ *= 1.0 / (double)t_list.size();
    summ = 1.0 / summ;

    return ResultToInt(summ);
}
