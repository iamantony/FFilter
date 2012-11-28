#ifndef CONSTNOISE_H
#define CONSTNOISE_H

#include <QImage>
#include <QColor>
#include <QDebug>
#include "defaultnoise.h"

class ConstNoise : public DefaultNoise
{
	// == METHODS ==
public:
	ConstNoise(const QImage &t_img,
			   const unsigned int &t_noiseLvl = 0,
			   const int &t_noiseAmp = 0,
			   QObject *parent = 0):
	  DefaultNoise(t_img, t_noiseLvl, t_noiseAmp, parent)
  {}

	QImage GetNoisedImage();

protected:
	QList<int> GenerateNoise();
};

#endif // CONSTNOISE_H
