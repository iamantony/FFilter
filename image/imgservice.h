#ifndef IMGSERVICE_H
#define IMGSERVICE_H

#include <QObject>
#include <QImage>

class ImgService : public QObject
{
    Q_OBJECT

    // == METHODS ==
public:
    explicit ImgService(QObject *parent = 0);

    // Transform color image to gray image
    QImage ColorImgToGray(const QImage &t_img);
    // Calc Standart Deviation (SD) between two images of the same size
    double CalcImgsSD(const QImage &t_firstImg, const QImage &t_secondImg);

signals:
    void SignalProgressPrc(int t_progress);
};

#endif // IMGSERVICE_H
