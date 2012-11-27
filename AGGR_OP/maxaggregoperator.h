#ifndef MAXAGGREGOPERATOR_H
#define MAXAGGREGOPERATOR_H

#include <math.h>
#include <QDebug>
#include "defaultaggregoperator.h"
#include "../DEFINES/common.h"
#include "../DEFINES/enums.h"

class MaxAggregOperator : public DefaultAggregOperator
{
	// == DATA ==
private:
	QList<long double> m_listOfValues;
	int m_result;

	// == METHODS ==
public:
	MaxAggregOperator();
	int GetWorthlyValue(const QList<long double> &t_list);

protected:
	void ResetValues();
};

#endif // MAXAGGREGOPERATOR_H
