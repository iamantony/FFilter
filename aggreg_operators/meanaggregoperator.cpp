#include "meanaggregoperator.h"

#include "common/common.h"

MeanAggregOperator::MeanAggregOperator(const double &t_power)
{
    if ( 0 == t_power )
    {
        m_power = 1;
    }
    else
    {
        m_power = (long double)t_power;
    }
}

int MeanAggregOperator::GetWorthyValue(const QList<long double> &t_list)
{
    if ( true == t_list.isEmpty() )
    {
        qDebug() << "MaxAggregOperator::GetWorthlyValue(): Error - list is empty!";
        return ERROR;
    }

    ResetValues();

    m_numOfValues = t_list.size();

    for (int i = 0; i < m_numOfValues; i++)
    {
        if ( 0 < t_list.at(i) )
        {
            m_summ += pow(t_list.at(i), m_power);
        }
    }

    m_summ /= (long double)m_numOfValues;
    m_summ = pow( m_summ, (1/m_power) );

    FormResult(m_summ);
    CheckResult();

    return m_result;
}

void MeanAggregOperator::ResetValues()
{
    m_summ = 0;
    m_numOfValues = 0;
    m_result = 0;
}
