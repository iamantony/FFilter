#ifndef FUNCAGGREGOPERATOR_H
#define FUNCAGGREGOPERATOR_H

#include <math.h>

#include <QList>
#include <QDebug>

#include "defaultaggregoperator.h"
#include "aggreg_operators/aggreg_operators.h"

class FuncAggregOperator : public DefaultAggregOperator
{
    // == DATA ==
private:
    long double (*m_directFunc) (long double);
    long double (*m_inverseFunc) (long double);
    int m_numOfValues;
    long double m_summ;

    // == METHODS ==
public:
    explicit FuncAggregOperator(const AggregOperator::Func::Type &t_func);
    int GetWorthlyValue(const QList<long double> &t_list);

protected:
    void ResetValues();
};

#endif // FUNCAGGREGOPERATOR_H
