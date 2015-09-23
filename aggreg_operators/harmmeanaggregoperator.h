#ifndef HARMMEANAGGREGOPERATOR_H
#define HARMMEANAGGREGOPERATOR_H

#include "defaultaggregoperator.h"

class HarmMeanAggregOperator : public DefaultAggregOperator
{
    // == METHODS ==
public:
    explicit HarmMeanAggregOperator() {}
    virtual ~HarmMeanAggregOperator() {}

    // Apply aggregation operator to list of values
    virtual int Calc(const QList<double>& t_list);
};

#endif // HARMMEANAGGREGOPERATOR_H
