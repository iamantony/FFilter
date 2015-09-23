#include "defaultaggregoperator.h"

#include <cmath>
#include <algorithm>

int DefaultAggregOperator::ResultToInt(const double& t_result) const
{
    int value = (int)std::floor(t_result + 0.5);

    value = std::max(value, 0);
    value = std::min(value, 255);

    return value;
}
