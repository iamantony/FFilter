#include "meanaggregoperator.h"

#include <cmath>
#include <limits>
#include <numeric>

#include <QDebug>

const double ZERO = 0.0;

MeanAggregOperator::MeanAggregOperator(const double &t_power)
{
    m_power = t_power;
    if ( std::abs(ZERO - m_power) <= std::numeric_limits<double>::epsilon() )
    {
        m_power = 1.0;
    }
}

int MeanAggregOperator::GetWorthyValue(const QList<double>& t_list)
{
    if ( true == t_list.isEmpty() )
    {
        qDebug() << __FUNCTION__ << "Error - list is empty";
        return 0;
    }

    ResetValues();

    auto accPower = [&m_power](const double& a, const double& b) {
        return a + std::pow(b, m_power);
    };

    m_summ = std::accumulate(
                 t_list.constBegin(), t_list.constEnd(), ZERO, accPower);

    m_summ /= (double)t_list.size();
    m_summ = pow( m_summ, (1/m_power) );

    FormResult(m_summ);
    CheckResult();

    return m_result;
}

void MeanAggregOperator::ResetValues()
{
    DefaultAggregOperator::ResetValues();
    m_summ = ZERO;
}
