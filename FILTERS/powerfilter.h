#ifndef POWERFILTER_H
#define POWERFILTER_H

#include <QObject>
#include <QImage>
#include <QColor>
#include <QDebug>
#include <math.h>
#include "AGGR_OP/defaultaggregoperator.h"
#include "DEFINES/common.h"

class PowerFilter : public QObject
{
	Q_OBJECT

	// == METHODS ==
public:
	explicit PowerFilter(QObject *parent = 0);
	QImage FilterImg(QImage t_noisyImg, DefaultAggregOperator *t_aggrOp);

signals:
	void SignalProcProgressPrc(int t_progress);

public slots:

};

#endif // POWERFILTER_H
