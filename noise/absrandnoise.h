#ifndef ABSRANDNOISE_H
#define ABSRANDNOISE_H

#include "noise/abstractnoise.h"

class QImage;

class AbsRandNoise : public AbstractNoise
{
    Q_OBJECT

    // == METHODS ==
public:
    explicit AbsRandNoise(const QImage &t_img,
                          const unsigned int &t_noiseLvl,
                          const int &t_noiseAmp);

    virtual ~AbsRandNoise() {}

protected:
    // Generate noise values
    virtual QVector<int> GenerateNoise();
};

#endif // ABSRANDNOISE_H
