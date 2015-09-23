#ifndef MEDAGGREGOPERATOR_H
#define MEDAGGREGOPERATOR_H

#include "defaultaggregoperator.h"

class MedAggregOperator : public DefaultAggregOperator
{
    // == METHODS ==
public:
    explicit MedAggregOperator() {}
    virtual ~MedAggregOperator() {}

    virtual int GetWorthyValue(const QList<double>& t_list);
};

#endif // MEDAGGREGOPERATOR_H
