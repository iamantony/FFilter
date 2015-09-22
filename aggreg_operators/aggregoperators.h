#ifndef AGGREG_OPERATORS_H
#define AGGREG_OPERATORS_H

namespace AggregOperator
{
    enum class Type
    {
        MIN = 0,
        MAX,
        MEAN,
        GEOMETRIC_MEAN,
        HARMONC_MAEN,
        MEDIAN,
        FUNCTIONAL,
        DEFAULT_LAST
    };

    enum class Func
    {
        EXP = 0,
        LOG_NATURAL,
        DEFAULT_LAST
    };
}

#endif // AGGREG_OPERATORS_H
