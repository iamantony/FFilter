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
 *	along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

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

namespace Noise
{
	enum NoiseType {
		CONSTANT = 0,
		RANDOM,
		ABS_RANDOM,
		DEFAULT_LAST
	};
}

#endif // ENUMS_H
