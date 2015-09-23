#ifndef MEANAGGREGOPERATOR_H
#define MEANAGGREGOPERATOR_H

#include "defaultaggregoperator.h"

class MeanAggregOperator : public DefaultAggregOperator
{
    // == METHODS ==
public:
    explicit MeanAggregOperator(const double& t_power);
    virtual ~MeanAggregOperator() {}

    // Apply aggregation operator to list of values
    virtual int Calc(const QList<double>& t_list);

    // == DATA ==
private:
    double m_power;
};

#endif // MEANAGGREGOPERATOR_H
