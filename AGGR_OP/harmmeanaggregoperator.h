#ifndef HARMMEANAGGREGOPERATOR_H
#define HARMMEANAGGREGOPERATOR_H

#include <math.h>
#include <QList>
#include <QDebug>
#include "defaultaggregoperator.h"
#include "../DEFINES/common.h"
#include "../DEFINES/enums.h"

class HarmMeanAggregOperator : public DefaultAggregOperator
{
	// == DATA ==
private:
	int m_numOfValues;
	long double m_summ;
	int m_result;

	// == METHODS ==
public:
	HarmMeanAggregOperator();
	int GetWorthlyValue(const QList<int> &t_list, int t_position = ERROR);

protected:
	void ResetValues();
};

#endif // HARMMEANAGGREGOPERATOR_H
