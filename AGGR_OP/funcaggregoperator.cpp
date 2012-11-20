#include "funcaggregoperator.h"

FuncAggregOperator::FuncAggregOperator(AggregOperatorFunc::AggrOpFunc t_func)
{
	switch(t_func)
	{
		case AggregOperatorFunc::EXP:
		{
			m_directFunc = &expl;
			m_inverseFunc = &logl;
			break;
		}
		case AggregOperatorFunc::LOG_NATURAL:
		{
			m_directFunc = &logl;
			m_inverseFunc = &expl;
			break;
		}
		default:
		{
			qDebug() << "FuncAggregOperator(): Error - undefined function type. Using defaults";
			m_directFunc = &expl;
			m_inverseFunc = &logl;
		}
	}

}

int FuncAggregOperator::GetWorthlyValue(const QList<int> &t_list, int t_position)
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
		m_summ += m_directFunc( (long double)t_list.at(i) );
	}

	m_summ *= (long double)1/m_numOfValues;
	m_summ = m_inverseFunc(m_summ);

	m_result = (int)floor(m_summ + 0.5);
	if ( m_result < 0 )
	{
		m_result = 0;
	}
	else if ( 255 < m_result )
	{
		m_result = 255;
	}

	return m_result;
}

void FuncAggregOperator::ResetValues()
{
	m_numOfValues = 0;
	m_summ = 0;
	m_result = 0;
}
