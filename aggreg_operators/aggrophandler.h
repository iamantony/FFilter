#ifndef AGGROPHANDLER_H
#define AGGROPHANDLER_H

#include <QObject>
#include <QSharedPointer>

#include "aggreg_operators/aggregoperators.h"
#include "aggreg_operators/defaultaggregoperator.h"

class AggrOpHandler : public QObject
{
    Q_OBJECT

    // == METHODS ==
public:
    explicit AggrOpHandler(QObject *parent = 0);
    virtual ~AggrOpHandler() {}

    AggregOperator::Type GetAggrOpType();
    double GetAggrOpPower();
    AggregOperator::Func GetAggrOpFunc();
    QSharedPointer<DefaultAggregOperator> GetAggrOperator();

private:
    void SetNewAggrOp();

signals:
    void SignalCurrAgOpType(AggregOperator::Type t_type);
    void SignalFuncType(AggregOperator::Func t_funcTyped);

public slots:
    void SlotSetAggrOpType(AggregOperator::Type t_type);
    void SlotSetAggrOpPower(double t_power);
    void SlotSetAggrOpFunc(AggregOperator::Func t_funcType);

    // == DATA ==
private:
    double m_power;
    AggregOperator::Type m_aggrOpType;
    AggregOperator::Func m_aggrOpFunc;
    QSharedPointer<DefaultAggregOperator> m_aggrOperator;
};

#endif // AGGROPHANDLER_H
