#ifndef MEDAGGREGOPERATOR_H
#define MEDAGGREGOPERATOR_H

#include <QList>
#include <QDebug>
#include "defaultaggregoperator.h"
#include "../DEFINES/common.h"
#include "../DEFINES/enums.h"

class MedAggregOperator : public DefaultAggregOperator
{
	// == DATA ==
private:
	QList<int> m_listOfValues;
	int m_numOfValues;
	int m_modulo;
	int m_mean;
	int m_result;

	// == METHODS ==
public:
	MedAggregOperator();
	int GetWorthlyValue(const QList<int> &t_list);

protected:
	void ResetValues();
};

#endif // MEDAGGREGOPERATOR_H
