#ifndef HARMMEANAGGREGOPERATOR_H
#define HARMMEANAGGREGOPERATOR_H

#include "defaultaggregoperator.h"

class HarmMeanAggregOperator : public DefaultAggregOperator
{
    // == METHODS ==
public:
    explicit HarmMeanAggregOperator() {}
    virtual ~HarmMeanAggregOperator() {}

    virtual int Calc(const QList<double>& t_list);
};

#endif // HARMMEANAGGREGOPERATOR_H
