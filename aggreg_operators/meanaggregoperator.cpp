#include "meanaggregoperator.h"

#include <cmath>
#include <limits>
#include <numeric>

#include <QDebug>

MeanAggregOperator::MeanAggregOperator(const double &t_power)
{
    m_power = t_power;
    if ( std::abs(m_power) <= std::numeric_limits<double>::epsilon() )
    {
        m_power = 1.0;
    }
}

// Apply aggregation operator to list of values
// @input:
// - t_list - list of values
// @output:
// - int - result of operation
int MeanAggregOperator::Calc(const QList<double>& t_list)
{
    if ( t_list.isEmpty() )
    {
        qDebug() << __FUNCTION__ << "Error - list is empty";
        return 0;
    }

    auto accPower = [this](const double& a, const double& b) {
        return a + std::pow(b, this->m_power);
    };

    double summ = std::accumulate(
                 t_list.constBegin(), t_list.constEnd(), 0.0, accPower);

    summ /= (double)t_list.size();
    summ = pow( summ, (1/m_power) );

    return ResultToInt(summ);
}
