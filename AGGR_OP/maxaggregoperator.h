#ifndef MAXAGGREGOPERATOR_H
#define MAXAGGREGOPERATOR_H

#include <QDebug>
#include "defaultaggregoperator.h"
#include "../DEFINES/common.h"
#include "../DEFINES/enums.h"

class MaxAggregOperator : public DefaultAggregOperator
{
	// == DATA ==
private:
	QList<int> m_listOfValues;

	// == METHODS ==
public:
	MaxAggregOperator();
	int GetWorthlyValue(const QList<int> &t_list, int t_position = ERROR);

protected:
	void ResetValues();
};

#endif // MAXAGGREGOPERATOR_H
