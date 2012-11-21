#ifndef DEFAULTAGGREGOPERATOR_H
#define DEFAULTAGGREGOPERATOR_H

#include <QObject>

class DefaultAggregOperator : public QObject
{
	Q_OBJECT

	// == METHODS ==
public:
	explicit DefaultAggregOperator(QObject *parent = 0);
	virtual int GetWorthlyValue(const QList<long double> &t_list) = 0;

protected:
	virtual void ResetValues() = 0;
};

#endif // DEFAULTAGGREGOPERATOR_H
