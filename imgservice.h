#ifndef IMGSERVICE_H
#define IMGSERVICE_H

#include <QObject>
#include <QImage>
#include <QColor>
#include <time.h>
#include <math.h>
#include <QDebug>
#include "DEFINES/common.h"

#define MIN_SKO 0.00001

class ImgService : public QObject
{
	Q_OBJECT

	// == METHODS ==
public:
	explicit ImgService(QObject *parent = 0);
	QImage TransColorImgToGrayImg(const QImage &t_img);
	QImage SetNoiseToImg(const QImage &img, const unsigned int &t_noiseLvl);
	double CalcImgsSKO(const QImage &t_firstImg, const QImage &t_secondImg);

signals:
	void SignalProcProgressPrc(int t_progress);

public slots:

};

#endif // IMGSERVICE_H
