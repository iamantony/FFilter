#include "geomeanaggregoperator.h"

#include <cmath>
#include <limits>
#include <QDebug>

const double ZERO = 0.0;

int GeoMeanAggregOperator::GetWorthyValue(const QList<double>& t_list)
{
    if ( true == t_list.isEmpty() )
    {
        qDebug() << __FUNCTION__ << "Error - list is empty";
        return 0;
    }

    ResetValues();

    // Calc product of all non-zero elements in list
    double product = ZERO;
    for (int i = 0; i < t_list.size(); ++i)
    {
        if ( std::numeric_limits<double>::epsilon() < std::abs(t_list.at(i)) )
        {
            if (std::numeric_limits<double>::epsilon() < std::abs(product))
            {
                product *= t_list.at(i);
            }
            else
            {
                product = t_list.at(i);
            }
        }
    }

    // If product is not equal to zero, calc root of it
    if (std::numeric_limits<double>::epsilon() < std::abs(product))
    {
        double power = 1.0 / (double)t_list.size();
        product = std::pow(product, power);
    }

    FormResult(product);
    CheckResult();

    return m_result;
}
