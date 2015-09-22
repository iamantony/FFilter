#ifndef AGGREG_OPERATORS_H
#define AGGREG_OPERATORS_H

namespace AggregOperator
{
    namespace Type
    {
        enum Type
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
    }

    namespace Func
    {
        enum Type
        {
            EXP = 0,
            LOG_NATURAL,
            DEFAULT_LAST
        };
    }
}

#endif // AGGREG_OPERATORS_H
