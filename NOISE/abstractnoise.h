#ifndef ABSTRACTNOISE_H
#define ABSTRACTNOISE_H

#include <QObject>
#include <QImage>
#include <QVector>

class AbstractNoise : public QObject
{
    Q_OBJECT

    // == METHODS ==
public:
    explicit AbstractNoise(const QImage &t_img,
                           const unsigned int &t_noiseLvl,
                           const int &t_noiseAmp);

    virtual ~AbstractNoise() {}

    // Get noised copy of image
    QImage GetNoisedImage();

protected:
    // Generate noise values
    virtual QVector<int> GenerateNoise() = 0;
    // Get number of pixels that should be noised
    unsigned int GetNumOfPixelsToNoise() const;

private:
    // Create map of pixels by whitch we can define should this pixel be noised
    // or not
    void CreatePixelsMap(const unsigned int &t_noiseLvl);

signals:
    void SignalProgressPrc(int t_progress);

    // == DATA ==
protected:
    int m_noiseAmplitude;

private:
    QVector< QVector<bool> > m_pixelsMap;
    QImage m_img;
};

#endif // ABSTRACTNOISE_H
