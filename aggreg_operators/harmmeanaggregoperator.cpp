#include "harmmeanaggregoperator.h"

#include <limits>

#include <QDebug>

const double ZERO = 0.0;

int HarmMeanAggregOperator::GetWorthyValue(const QList<double>& t_list)
{
    if ( t_list.isEmpty() )
    {
        qDebug() << __FUNCTION__ << "Error - list is empty";
        return 0;
    }

    ResetValues();

    double summ = ZERO;
    for (int i = 0; i < t_list.size(); ++i)
    {
        if ( std::numeric_limits<double>::epsilon() < std::abs(t_list.at(i)) )
        {
            summ += 1 / t_list.at(i);
        }
    }

    summ *= 1.0 / (double)t_list.size();
    summ = 1.0 / summ;

    FormResult(summ);
    CheckResult();

    return m_result;
}
