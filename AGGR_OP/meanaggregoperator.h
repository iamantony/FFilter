#ifndef MEANAGGREGOPERATOR_H
#define MEANAGGREGOPERATOR_H

#include <math.h>
#include <QList>
#include <QDebug>
#include "defaultaggregoperator.h"
#include "../DEFINES/common.h"
#include "../DEFINES/enums.h"

class MeanAggregOperator : public DefaultAggregOperator
{
	// == DATA ==
private:
	long double m_power;
	long double m_summ;
	int m_result;
	int m_numOfValues;

	// == METHODS ==
public:
	MeanAggregOperator(const double &t_power);
	int GetWorthlyValue(const QList<int> &t_list);

protected:
	void ResetValues();
};

#endif // MEANAGGREGOPERATOR_H
