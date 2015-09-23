#ifndef DEFAULTAGGREGOPERATOR_H
#define DEFAULTAGGREGOPERATOR_H

#include <QList>

class DefaultAggregOperator
{
    // == METHODS ==
public:
    explicit DefaultAggregOperator() {}
    virtual ~DefaultAggregOperator() {}

    virtual int GetWorthyValue(const QList<double>& t_list) = 0;

protected:
    int ResultToInt(const double& t_result) const;
};

#endif // DEFAULTAGGREGOPERATOR_H
