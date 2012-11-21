#ifndef POWERFILTER_H
#define POWERFILTER_H

#include <QObject>
#include <QImage>
#include <QColor>
#include <QDebug>
#include "MASKS/maskstructure.h"
#include "AGGR_OP/defaultaggregoperator.h"
#include "DEFINES/common.h"

class PowerFilter : public QObject
{
	Q_OBJECT

	// == DATA ==
private:
	MaskStructure *m_mask;
	DefaultAggregOperator *m_aggregOperator;

	// == METHODS ==
public:
	explicit PowerFilter(QObject *parent = 0);
	~PowerFilter();

	void Init(MaskStructure *t_mask, DefaultAggregOperator *t_aggrOp);
	QImage FilterImg(const QImage &t_noisyImg);

private:
	void SetDefaults();

signals:
	void SignalProcProgressPrc(int t_progress);

};

#endif // POWERFILTER_H
