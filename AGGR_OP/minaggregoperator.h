#ifndef MINAGGREGOPERATOR_H
#define MINAGGREGOPERATOR_H

#include <QDebug>
#include "defaultaggregoperator.h"
#include "../DEFINES/common.h"
#include "../DEFINES/enums.h"

class MinAggregOperator : public DefaultAggregOperator
{
	// == DATA ==
private:
	QList<int> m_listOfValues;

	// == METHODS ==
public:
	MinAggregOperator();
	int GetWorthlyValue(const QList<int> &t_list);

protected:
	void ResetValues();
};

#endif // MINAGGREGOPERATOR_H
