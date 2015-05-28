#ifndef MINAGGREGOPERATOR_H
#define MINAGGREGOPERATOR_H

#include <math.h>
#include <QDebug>
#include "defaultaggregoperator.h"

class MinAggregOperator : public DefaultAggregOperator
{
    // == DATA ==
private:
    QList<long double> m_listOfValues;

    // == METHODS ==
public:
    MinAggregOperator();
    int GetWorthlyValue(const QList<long double> &t_list);

protected:
    void ResetValues();
};

#endif // MINAGGREGOPERATOR_H
