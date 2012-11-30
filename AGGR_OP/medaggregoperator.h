#ifndef MEDAGGREGOPERATOR_H
#define MEDAGGREGOPERATOR_H

#include <math.h>
#include <QList>
#include <QDebug>
#include "defaultaggregoperator.h"
#include "../DEFINES/common.h"
#include "../DEFINES/enums.h"

class MedAggregOperator : public DefaultAggregOperator
{
	// == DATA ==
private:
	QList<long double> m_listOfValues;
	int m_numOfValues;
	int m_modulo;
	int m_mean;
	long double m_summ;

	// == METHODS ==
public:
	MedAggregOperator();
	int GetWorthlyValue(const QList<long double> &t_list);

protected:
	void ResetValues();
};

#endif // MEDAGGREGOPERATOR_H
