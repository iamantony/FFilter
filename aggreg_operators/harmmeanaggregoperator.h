#ifndef HARMMEANAGGREGOPERATOR_H
#define HARMMEANAGGREGOPERATOR_H

#include <math.h>
#include <QList>
#include <QDebug>
#include "defaultaggregoperator.h"

class HarmMeanAggregOperator : public DefaultAggregOperator
{
    // == DATA ==
private:
    int m_numOfValues;
    long double m_summ;

    // == METHODS ==
public:
    HarmMeanAggregOperator();
    int GetWorthyValue(const QList<long double> &t_list);

protected:
    void ResetValues();
};

#endif // HARMMEANAGGREGOPERATOR_H
