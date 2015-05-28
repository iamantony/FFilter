#ifndef AGGROPHANDLER_H
#define AGGROPHANDLER_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QDebug>
#include "defaultaggregoperator.h"
#include "maxaggregoperator.h"
#include "minaggregoperator.h"
#include "meanaggregoperator.h"
#include "geomeanaggregoperator.h"
#include "harmmeanaggregoperator.h"
#include "medaggregoperator.h"
#include "funcaggregoperator.h"

class AggrOpHandler : public QObject
{
    Q_OBJECT

    // == DATA ==
private:
    AggregOperator::Type::Type m_aggrOpType;
    double m_power;
    AggregOperator::Func::Type m_aggrOpFunc;
    DefaultAggregOperator *m_aggrOperator;

    // == METHODS ==
public:
    explicit AggrOpHandler(QObject *parent = 0);
    ~AggrOpHandler();
    AggregOperator::Type::Type GetAggrOpType();
    double GetAggrOpPower();
    AggregOperator::Func::Type GetAggrOpFunc();
    DefaultAggregOperator* GetAggrOperator();

private:
    void SetNewAggrOp();

signals:
    void SignalCurrAgOpType(AggregOperator::Type::Type t_type);
    void SignalFuncType(AggregOperator::Func::Type t_funcTyped);

public slots:
    void SlotSetAggrOpType(AggregOperator::Type::Type t_type);
    void SlotSetAggrOpPower(double t_power);
    void SlotSetAggrOpFunc(AggregOperator::Func::Type t_funcType);

};

#endif // AGGROPHANDLER_H
