#include "geomeanaggregoperator.h"

#include <cmath>
#include <limits>
#include <QDebug>

// Apply aggregation operator to list of values
// @input:
// - t_list - list of values
// @output:
// - int - result of operation
int GeoMeanAggregOperator::Calc(const QList<double>& t_list)
{
    if ( t_list.isEmpty() )
    {
        qDebug() << __FUNCTION__ << "Error - list is empty";
        return 0;
    }

    // Calc product of all non-zero elements in list
    double product = 0.0;
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

    return ResultToInt(product);
}
