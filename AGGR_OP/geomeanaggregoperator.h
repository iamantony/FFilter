#ifndef GEOMEANAGGREGOPERATOR_H
#define GEOMEANAGGREGOPERATOR_H

#include <math.h>
#include <QList>
#include <QDebug>
#include "defaultaggregoperator.h"
#include "../DEFINES/common.h"
#include "../DEFINES/enums.h"

class GeoMeanAggregOperator : public DefaultAggregOperator
{
	// == DATA ==
private:
	int m_numOfValues;
	long double m_product;
	int m_startValue;
	long double m_power;
	long double m_rootedProduct;
	int m_result;

	// == METHODS ==
public:
	GeoMeanAggregOperator();
	int GetWorthlyValue(const QList<int> &t_list);

protected:
	void ResetValues();
};

#endif // GEOMEANAGGREGOPERATOR_H
