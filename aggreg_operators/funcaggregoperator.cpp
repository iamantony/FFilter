#include "funcaggregoperator.h"

#include "common/common.h"

FuncAggregOperator::FuncAggregOperator(const AggregOperator::Func& t_func)
{
    switch(t_func)
    {
        case AggregOperator::Func::EXP:
        {
            m_directFunc = &expl;
            m_inverseFunc = &logl;
            break;
        }

        case AggregOperator::Func::LOG_NATURAL:
        {
            m_directFunc = &logl;
            m_inverseFunc = &expl;
            break;
        }

        case AggregOperator::Func::DEFAULT_LAST:
        default:
        {
            qDebug() << "FuncAggregOperator(): Error - undefined function type. Using defaults";
            m_directFunc = &expl;
            m_inverseFunc = &logl;
        }
    }

}

int FuncAggregOperator::GetWorthlyValue(const QList<long double> &t_list)
{
    if ( true == t_list.isEmpty() )
    {
        qDebug() << "FuncAggregOperator::GetWorthlyValue(): Error - list is empty!";
        return ERROR;
    }

    ResetValues();

    m_numOfValues = t_list.size();

    for (int i = 0; i < m_numOfValues; i++)
    {
        m_summ += m_directFunc( 1 + t_list.at(i) );
    }

    m_summ *= (long double)1/m_numOfValues;
    m_summ = m_inverseFunc(m_summ);

    FormResult(m_summ);
    CheckResult();

    return m_result;
}

void FuncAggregOperator::ResetValues()
{
    m_numOfValues = 0;
    m_summ = 0;
    m_result = 0;
}
