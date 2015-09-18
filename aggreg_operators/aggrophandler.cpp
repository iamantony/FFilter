#include "aggrophandler.h"

AggrOpHandler::AggrOpHandler(QObject *parent) :
    QObject(parent)
{
    m_aggrOpType = AggregOperator::Type::MIN;
    m_aggrOpFunc = AggregOperator::Func::EXP;
    m_power = 1;
    m_aggrOperator = nullptr;
}

AggrOpHandler::~AggrOpHandler()
{
    delete m_aggrOperator;
}

AggregOperator::Type::Type AggrOpHandler::GetAggrOpType()
{
    return m_aggrOpType;
}

double AggrOpHandler::GetAggrOpPower()
{
    return m_power;
}

AggregOperator::Func::Type AggrOpHandler::GetAggrOpFunc()
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
        case AggregOperator::Type::MIN:
            m_aggrOperator = new MinAggregOperator();
            break;

        case AggregOperator::Type::MAX:
            m_aggrOperator = new MaxAggregOperator();
            break;

        case AggregOperator::Type::MEAN:
            m_aggrOperator = new MeanAggregOperator(m_power);
            break;

        case AggregOperator::Type::GEOMETRIC_MEAN:
            m_aggrOperator = new GeoMeanAggregOperator();
            break;

        case AggregOperator::Type::HARMONC_MAEN:
            m_aggrOperator = new HarmMeanAggregOperator();
            break;

        case AggregOperator::Type::MEDIAN:
            m_aggrOperator = new MedAggregOperator();
            break;

        case AggregOperator::Type::FUNCTIONAL:
            m_aggrOperator = new FuncAggregOperator(m_aggrOpFunc);
            break;

        case AggregOperator::Type::DEFAULT_LAST:
        default:
        {
            qDebug() << "SetNewAggrOp(): undefined aggregation operator type. Min operator set.";
            m_aggrOpType = AggregOperator::Type::MIN;
            m_aggrOperator = new MinAggregOperator();
        }
    }
}

void AggrOpHandler::SlotSetAggrOpType(AggregOperator::Type::Type t_type)
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

void AggrOpHandler::SlotSetAggrOpFunc(AggregOperator::Func::Type t_funcType)
{
    m_aggrOpFunc = t_funcType;
}
