#ifndef NOISE_H
#define NOISE_H

namespace Noise
{
    enum Type
    {
        CONSTANT = 0,
        RANDOM,
        ABS_RANDOM,
        DEFAULT_LAST
    };

    const int MIN_NOISE_AMP = -255;
    const int MAX_NOISE_AMP = 255;
    const unsigned int MAX_PERCENT = 100;
    const int MIN_LUMINANCE = 0;
    const int MAX_LUMINANCE = 255;
}

#endif // NOISE_H
