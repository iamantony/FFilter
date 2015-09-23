#include "defaultaggregoperator.h"

#include <math.h>

void DefaultAggregOperator::ResetValues()
{
    m_result = 0;
}

void DefaultAggregOperator::CheckResult()
{
    if ( m_result < 0 )
    {
        m_result = 0;
    }
    else if ( 255 < m_result )
    {
        m_result = 255;
    }
}

void DefaultAggregOperator::FormResult(const long double& t_result)
{
    m_result = (int)floor(t_result + 0.5);
}
