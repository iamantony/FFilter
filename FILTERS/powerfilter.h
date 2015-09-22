#ifndef POWERFILTER_H
#define POWERFILTER_H

#include <QObject>
#include <QSharedPointer>

#include "masks/mask.h"
#include "aggreg_operators/defaultaggregoperator.h"

class QImage;

class PowerFilter : public QObject
{
    Q_OBJECT

    // == METHODS ==
public:
    explicit PowerFilter(QObject *parent = 0);
    virtual ~PowerFilter() {}

    bool Init(QSharedPointer<Mask> t_mask,
              QSharedPointer<DefaultAggregOperator> t_aggrOp);
    QImage FilterImg(const QImage &t_noisyImg);

signals:
    void SignalProgressPrc(int t_progress);
    void SignalFiltrationFinished();

    // == DATA ==
private:
    QSharedPointer<Mask> m_mask;
    QSharedPointer<DefaultAggregOperator> m_aggregOperator;
};

#endif // POWERFILTER_H
