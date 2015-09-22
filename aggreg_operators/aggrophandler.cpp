#include "aggrophandler.h"

#include <QDebug>

#include "minaggregoperator.h"
#include "maxaggregoperator.h"
#include "meanaggregoperator.h"
#include "geomeanaggregoperator.h"
#include "harmmeanaggregoperator.h"
#include "medaggregoperator.h"
#include "funcaggregoperator.h"

AggrOpHandler::AggrOpHandler(QObject *parent) :
    QObject(parent)
{
    m_aggrOpType = AggregOperator::Type::MIN;
    m_aggrOpFunc = AggregOperator::Func::EXP;
    m_power = 1.0;
}

AggregOperator::Type AggrOpHandler::GetAggrOpType()
{
    return m_aggrOpType;
}

double AggrOpHandler::GetAggrOpPower()
{
    return m_power;
}

AggregOperator::Func AggrOpHandler::GetAggrOpFunc()
{
    return m_aggrOpFunc;
}

QSharedPointer<DefaultAggregOperator> AggrOpHandler::GetAggrOperator()
{
    SetNewAggrOp();
    return QSharedPointer<DefaultAggregOperator>(m_aggrOperator);
}

void AggrOpHandler::SetNewAggrOp()
{
    switch(m_aggrOpType)
    {
        case AggregOperator::Type::MIN:
            m_aggrOperator =
                QSharedPointer<DefaultAggregOperator>(new MinAggregOperator());
            break;

        case AggregOperator::Type::MAX:
            m_aggrOperator =
                QSharedPointer<DefaultAggregOperator>(new MaxAggregOperator());
            break;

        case AggregOperator::Type::MEAN:
            m_aggrOperator = QSharedPointer<DefaultAggregOperator>(
                                 new MeanAggregOperator(m_power));
            break;

        case AggregOperator::Type::GEOMETRIC_MEAN:
            m_aggrOperator = QSharedPointer<DefaultAggregOperator>(
                                 new GeoMeanAggregOperator());
            break;

        case AggregOperator::Type::HARMONC_MAEN:
            m_aggrOperator = QSharedPointer<DefaultAggregOperator>(
                                 new HarmMeanAggregOperator());
            break;

        case AggregOperator::Type::MEDIAN:
            m_aggrOperator =
                QSharedPointer<DefaultAggregOperator>(new MedAggregOperator());
            break;

        case AggregOperator::Type::FUNCTIONAL:
            m_aggrOperator = QSharedPointer<DefaultAggregOperator>(
                                 new FuncAggregOperator(m_aggrOpFunc));
            break;

        case AggregOperator::Type::DEFAULT_LAST:
        default:
        {
            qDebug() << __FUNCTION__ <<
                        "Set default aggregational operator: min operator";
            m_aggrOpType = AggregOperator::Type::MIN;
            m_aggrOperator =
                QSharedPointer<DefaultAggregOperator>(new MinAggregOperator());
        }
    }
}

void AggrOpHandler::SlotSetAggrOpType(AggregOperator::Type t_type)
{
    m_aggrOpType = t_type;
}

void AggrOpHandler::SlotSetAggrOpPower(double t_power)
{
    m_power = t_power;
}

void AggrOpHandler::SlotSetAggrOpFunc(AggregOperator::Func t_funcType)
{
    m_aggrOpFunc = t_funcType;
}
