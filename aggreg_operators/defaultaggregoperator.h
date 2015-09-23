#ifndef DEFAULTAGGREGOPERATOR_H
#define DEFAULTAGGREGOPERATOR_H

#include <QList>

class DefaultAggregOperator
{
    // == METHODS ==
public:
    explicit DefaultAggregOperator() {}
    virtual ~DefaultAggregOperator() {}

    // Apply aggregation operator to list of values
    virtual int Calc(const QList<double>& t_list) = 0;

protected:
    // Transform double to int with value between [0, 255]
    int ResultToInt(const double& t_result) const;
};

#endif // DEFAULTAGGREGOPERATOR_H
