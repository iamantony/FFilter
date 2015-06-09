#ifndef IMGSERVICE_H
#define IMGSERVICE_H

#include <QObject>
#include <QImage>
#include <QColor>
#include <time.h>
#include <math.h>
#include <QDebug>

#define MIN_SKO 0.00001

class ImgService : public QObject
{
    Q_OBJECT

    // == METHODS ==
public:
    explicit ImgService(QObject *parent = 0);

    QImage TransColorImgToGrayImg(const QImage &t_img);
    double CalcImgsSD(const QImage &t_firstImg, const QImage &t_secondImg);

signals:
    void SignalProgressPrc(int t_progress);
};

#endif // IMGSERVICE_H
