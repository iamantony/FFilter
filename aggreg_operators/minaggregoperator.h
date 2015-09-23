#ifndef MINAGGREGOPERATOR_H
#define MINAGGREGOPERATOR_H

#include "defaultaggregoperator.h"

class MinAggregOperator : public DefaultAggregOperator
{
    // == METHODS ==
public:
    explicit MinAggregOperator() {}
    virtual ~MinAggregOperator() {}

    virtual int GetWorthyValue(const QList<long double>& t_list);
};

#endif // MINAGGREGOPERATOR_H
