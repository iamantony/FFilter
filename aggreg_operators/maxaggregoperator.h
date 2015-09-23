#ifndef MAXAGGREGOPERATOR_H
#define MAXAGGREGOPERATOR_H

#include "defaultaggregoperator.h"

class MaxAggregOperator : public DefaultAggregOperator
{
    // == METHODS ==
public:
    explicit MaxAggregOperator() {}
    virtual ~MaxAggregOperator() {}

    virtual int GetWorthyValue(const QList<long double>& t_list);
};

#endif // MAXAGGREGOPERATOR_H
