#include "funcaggregoperator.h"

#include <cmath>

#include <QDebug>

FuncAggregOperator::FuncAggregOperator(const AggregOperator::Func& t_func)
{
    switch(t_func)
    {
        case AggregOperator::Func::LOG_NATURAL:
        {
            m_directFunc = &std::log;
            m_inverseFunc = &std::exp;
            break;
        }

        case AggregOperator::Func::EXP:
        case AggregOperator::Func::DEFAULT_LAST:
        default:
        {
            m_directFunc = &std::exp;
            m_inverseFunc = &std::log;
        }
    }
}

// Apply aggregation operator to list of values
// @input:
// - t_list - list of values
// @output:
// - int - result of operation
int FuncAggregOperator::Calc(const QList<double>& t_list)
{
    if ( t_list.isEmpty() )
    {
        qDebug() << __FUNCTION__ << "Error - list is empty";
        return 0;
    }

    double summ = 0.0;
    for (int i = 0; i < t_list.size(); ++i)
    {
        summ += m_directFunc( 1 + t_list.at(i) );
    }

    summ *= 1.0 / t_list.size();
    summ = m_inverseFunc(summ);

    return ResultToInt(summ);
}
