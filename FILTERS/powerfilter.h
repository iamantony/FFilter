#ifndef POWERFILTER_H
#define POWERFILTER_H

#include <QObject>
#include <QImage>
#include <QSharedPointer>

#include "masks/mask.h"
#include "aggreg_operators/defaultaggregoperator.h"

class PowerFilter : public QObject
{
    Q_OBJECT

    // == METHODS ==
public:
    explicit PowerFilter(QObject *parent = 0);
    ~PowerFilter();

    void Init(QSharedPointer<Mask> t_mask, DefaultAggregOperator *t_aggrOp);
    QImage FilterImg(const QImage &t_noisyImg);

private:
    void SetDefaults();

signals:
    void SignalProgressPrc(int t_progress);
    void SignalFiltrationFinished();

    // == DATA ==
private:
    QSharedPointer<Mask> m_mask;
    DefaultAggregOperator *m_aggregOperator;
};

#endif // POWERFILTER_H
