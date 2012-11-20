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
#include "../DEFINES/common.h"
#include "../DEFINES/enums.h"

class AggrOpHandler : public QObject
{
	Q_OBJECT

	// == DATA ==
private:
	AggregOperatorType::AggrOpType m_aggrOpType;
	double m_power;
	AggregOperatorFunc::AggrOpFunc m_aggrOpFunc;
	DefaultAggregOperator *m_aggrOperator;

	// == METHODS ==
public:
	explicit AggrOpHandler(QObject *parent = 0);
	~AggrOpHandler();
	AggregOperatorType::AggrOpType GetAggrOpType();
	double GetAggrOpPower();
	AggregOperatorFunc::AggrOpFunc GetAggrOpFunc();
	DefaultAggregOperator* GetAggrOperator();

private:
	void SetNewAggrOp();

signals:
	void SignalCurrAgOpType(AggregOperatorType::AggrOpType t_type);
	void SignalFuncType(AggregOperatorFunc::AggrOpFunc t_funcTyped);

public slots:
	void SlotSetAggrOpType(AggregOperatorType::AggrOpType t_type);
	void SlotSetAggrOpPower(double t_power);
	void SlotSetAggrOpFunc(AggregOperatorFunc::AggrOpFunc t_funcType);

};

#endif // AGGROPHANDLER_H
