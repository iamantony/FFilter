#ifndef FUNCAGGREGOPERATOR_H
#define FUNCAGGREGOPERATOR_H

#include <math.h>
#include <QList>
#include <QDebug>
#include "defaultaggregoperator.h"
#include "../DEFINES/common.h"
#include "../DEFINES/enums.h"

class FuncAggregOperator : public DefaultAggregOperator
{
	// == DATA ==
private:
	long double (*m_directFunc) (long double);
	long double (*m_inverseFunc) (long double);
	int m_numOfValues;
	long double m_summ;
	int m_result;

	// == METHODS ==
public:
	FuncAggregOperator(AggregOperatorFunc::AggrOpFunc t_func);
	int GetWorthlyValue(const QList<int> &t_list);

protected:
	void ResetValues();
};

#endif // FUNCAGGREGOPERATOR_H
