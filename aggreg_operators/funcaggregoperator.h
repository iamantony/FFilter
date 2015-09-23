#ifndef FUNCAGGREGOPERATOR_H
#define FUNCAGGREGOPERATOR_H

#include "defaultaggregoperator.h"
#include "aggreg_operators/aggregoperators.h"

class FuncAggregOperator : public DefaultAggregOperator
{
    // == METHODS ==
public:
    explicit FuncAggregOperator(const AggregOperator::Func &t_func);
    virtual ~FuncAggregOperator() {}

    // Apply aggregation operator to list of values
    virtual int Calc(const QList<double>& t_list);

    // == DATA ==
private:
    double (*m_directFunc) (double);
    double (*m_inverseFunc) (double);
};

#endif // FUNCAGGREGOPERATOR_H
