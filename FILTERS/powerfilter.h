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

    // Initialize
    bool Init(QSharedPointer<Mask> t_mask,
              QSharedPointer<DefaultAggregOperator> t_aggrOp);

    // Perform image filtration
    QImage FilterImg(const QImage &t_img);

signals:
    void SignalProgressPrc(const int& t_progress);
    void SignalFiltrationFinished();

    // == DATA ==
private:
    QSharedPointer<Mask> m_mask;
    QSharedPointer<DefaultAggregOperator> m_aggregOperator;
};

#endif // POWERFILTER_H
