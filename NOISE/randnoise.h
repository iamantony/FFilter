#ifndef RANDNOISE_H
#define RANDNOISE_H

#include <QImage>

#include "noise/abstractnoise.h"

class RandNoise : public AbstractNoise
{
    Q_OBJECT

    // == METHODS ==
public:
    explicit RandNoise(const QImage &t_img,
                       const unsigned int &t_noiseLvl,
                       const int &t_noiseAmp);

    virtual ~RandNoise();

protected:
    // Generate noise values
    virtual QVector<int> GenerateNoise();
};

#endif // RANDNOISE_H
