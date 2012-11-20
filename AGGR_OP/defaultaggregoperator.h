#ifndef DEFAULTAGGREGOPERATOR_H
#define DEFAULTAGGREGOPERATOR_H

#include <QObject>
#include "../DEFINES/common.h"

class DefaultAggregOperator : public QObject
{
	Q_OBJECT

	// == METHODS ==
public:
	explicit DefaultAggregOperator(QObject *parent = 0);
	virtual int GetWorthlyValue(const QList<int> &t_list) = 0;

protected:
	virtual void ResetValues() = 0;
};

#endif // DEFAULTAGGREGOPERATOR_H
