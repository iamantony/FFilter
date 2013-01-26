/* === This file is part of FFilter ===
 *
 *	Copyright 2012, Antony Cherepanov <antony.cherepanov@gmail.com>
 *
 *	FFilter is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	FFilter is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with FFilter. If not, see <http://www.gnu.org/licenses/>.
 */

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
