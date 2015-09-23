#ifndef MEANAGGREGOPERATOR_H
#define MEANAGGREGOPERATOR_H

#include "defaultaggregoperator.h"

class MeanAggregOperator : public DefaultAggregOperator
{
    // == METHODS ==
public:
    explicit MeanAggregOperator(const double& t_power);
    virtual ~MeanAggregOperator() {}

    virtual int GetWorthyValue(const QList<double>& t_list);

protected:
    void ResetValues();

    // == DATA ==
private:
    double m_power;
    double m_summ;
};

#endif // MEANAGGREGOPERATOR_H
