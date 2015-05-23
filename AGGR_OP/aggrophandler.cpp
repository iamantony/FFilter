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

#include "aggrophandler.h"

AggrOpHandler::AggrOpHandler(QObject *parent) :
	QObject(parent)
{
	m_aggrOpType = AggregOperatorType::MIN;
	m_aggrOpFunc = AggregOperatorFunc::EXP;
	m_power = 1;
	m_aggrOperator = NULL;
}

AggrOpHandler::~AggrOpHandler()
{
	delete m_aggrOperator;
}

AggregOperatorType::AggrOpType AggrOpHandler::GetAggrOpType()
{
	return m_aggrOpType;
}

double AggrOpHandler::GetAggrOpPower()
{
	return m_power;
}

AggregOperatorFunc::AggrOpFunc AggrOpHandler::GetAggrOpFunc()
{
	return m_aggrOpFunc;
}

DefaultAggregOperator* AggrOpHandler::GetAggrOperator()
{
	SetNewAggrOp();
	return m_aggrOperator;
}

void AggrOpHandler::SetNewAggrOp()
{
	delete m_aggrOperator;

	switch(m_aggrOpType)
	{
		case AggregOperatorType::MIN:
			m_aggrOperator = new MinAggregOperator();
			break;

		case AggregOperatorType::MAX:
			m_aggrOperator = new MaxAggregOperator();
			break;

		case AggregOperatorType::MEAN:
			m_aggrOperator = new MeanAggregOperator(m_power);
			break;

		case AggregOperatorType::GEOMETRIC_MEAN:
			m_aggrOperator = new GeoMeanAggregOperator();
			break;

		case AggregOperatorType::HARMONC_MAEN:
			m_aggrOperator = new HarmMeanAggregOperator();
			break;

		case AggregOperatorType::MEDIAN:
			m_aggrOperator = new MedAggregOperator();
			break;

		case AggregOperatorType::FUNCTIONAL:
			m_aggrOperator = new FuncAggregOperator(m_aggrOpFunc);
			break;

		case AggregOperatorType::DEFAULT_LAST:
		default:
		{
			qDebug() << "SetNewAggrOp(): undefined aggregation operator type. Min operator set.";
			m_aggrOpType = AggregOperatorType::MIN;
			m_aggrOperator = new MinAggregOperator();
		}
	}
}

void AggrOpHandler::SlotSetAggrOpType(AggregOperatorType::AggrOpType t_type)
{
	if (0 == t_type)
	{
		qDebug() << "123";
	}

	m_aggrOpType = t_type;
}

void AggrOpHandler::SlotSetAggrOpPower(double t_power)
{
	m_power = t_power;
}

void AggrOpHandler::SlotSetAggrOpFunc(AggregOperatorFunc::AggrOpFunc t_funcType)
{
	m_aggrOpFunc = t_funcType;
}
