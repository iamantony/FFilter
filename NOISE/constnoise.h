#ifndef CONSTNOISE_H
#define CONSTNOISE_H

#include <QImage>

#include "noise/abstractnoise.h"

class ConstNoise : public AbstractNoise
{
    Q_OBJECT

    // == METHODS ==
public:
    explicit ConstNoise(const QImage &t_img,
                        const unsigned int &t_noiseLvl,
                        const int &t_noiseAmp);

    virtual ~ConstNoise();

    virtual QImage GetNoisedImage();

protected:
    virtual QList<int> GenerateNoise();
};

#endif // CONSTNOISE_H
