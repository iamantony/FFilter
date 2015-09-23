#ifndef GEOMEANAGGREGOPERATOR_H
#define GEOMEANAGGREGOPERATOR_H

#include "defaultaggregoperator.h"

class GeoMeanAggregOperator : public DefaultAggregOperator
{
    // == METHODS ==
public:
    explicit GeoMeanAggregOperator() {}
    virtual ~GeoMeanAggregOperator() {}

    virtual int GetWorthyValue(const QList<double>& t_list);
};

#endif // GEOMEANAGGREGOPERATOR_H
