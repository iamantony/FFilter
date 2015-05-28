#ifndef DEFAULTAGGREGOPERATOR_H
#define DEFAULTAGGREGOPERATOR_H

#include <QObject>
#include <math.h>

class DefaultAggregOperator : public QObject
{
    Q_OBJECT
    // == DATA ==
protected:
    int m_result;

    // == METHODS ==
public:
    explicit DefaultAggregOperator(QObject *parent = 0);
    virtual int GetWorthlyValue(const QList<long double> &t_list) = 0;

protected:
    virtual void ResetValues() = 0;
    void CheckResult();
    void FormResult(const long double &t_result);
};

#endif // DEFAULTAGGREGOPERATOR_H
