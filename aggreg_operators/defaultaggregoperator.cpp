#include "defaultaggregoperator.h"

#include <cmath>
#include <algorithm>

// Transform double to int with value between [0, 255]
// @input:
// - t_result - some value
// @output:
// - int - transformed input value that was constrained to [0, 255]
int DefaultAggregOperator::ResultToInt(const double& t_result) const
{
    int value = (int)std::floor(t_result + 0.5);

    value = std::max(value, 0);
    value = std::min(value, 255);

    return value;
}
