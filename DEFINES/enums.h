#ifndef ENUMS_H
#define ENUMS_H

namespace ImageMode
{
	enum ImgMode {
		GRAYSCALE = 0,
		COLOR,
		DEFAULT_LAST
	};
}

namespace AggregOperatorType
{
	enum AggrOpType {
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

namespace AggregOperatorFunc
{
	enum AggrOpFunc {
		EXP = 0,
		LOG_NATURAL,
		DEFAULT_LAST
	};
}

#endif // ENUMS_H
