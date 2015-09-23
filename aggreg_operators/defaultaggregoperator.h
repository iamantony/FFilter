#ifndef DEFAULTAGGREGOPERATOR_H
#define DEFAULTAGGREGOPERATOR_H

#include <QList>

class DefaultAggregOperator
{
    // == METHODS ==
public:
    explicit DefaultAggregOperator() : m_result(0) {}
    virtual ~DefaultAggregOperator() {}

    virtual int GetWorthyValue(const QList<double>& t_list) = 0;

protected:
    virtual void ResetValues();
    void CheckResult();
    void FormResult(const long double& t_result);

    // == DATA ==
protected:
    int m_result;
};

#endif // DEFAULTAGGREGOPERATOR_H
