#ifndef MINAGGREGOPERATOR_H
#define MINAGGREGOPERATOR_H

#include "defaultaggregoperator.h"

class MinAggregOperator : public DefaultAggregOperator
{
    // == METHODS ==
public:
    explicit MinAggregOperator() {}
    virtual ~MinAggregOperator() {}

    // Apply aggregation operator to list of values
    virtual int Calc(const QList<double>& t_list);
};

#endif // MINAGGREGOPERATOR_H
