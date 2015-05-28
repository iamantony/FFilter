#ifndef MAXAGGREGOPERATOR_H
#define MAXAGGREGOPERATOR_H

#include <math.h>
#include <QDebug>
#include "defaultaggregoperator.h"

class MaxAggregOperator : public DefaultAggregOperator
{
    // == DATA ==
private:
    QList<long double> m_listOfValues;

    // == METHODS ==
public:
    MaxAggregOperator();
    int GetWorthlyValue(const QList<long double> &t_list);

protected:
    void ResetValues();
};

#endif // MAXAGGREGOPERATOR_H
