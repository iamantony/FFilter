#ifndef DEFAULTNOISE_H
#define DEFAULTNOISE_H

#include <QObject>
#include <QImage>
#include <time.h>
#include <QDebug>

class DefaultNoise : public QObject
{
	Q_OBJECT
	// == DATA ==
protected:
	QImage m_imgToNoise;
	int m_noiseAmplitude;
	unsigned int m_noiseLevelPercent;
	unsigned int m_pixelsToNoise;
	unsigned int m_numPixToChange;
	bool m_needToNoise;
	bool **m_pixelsToChange;

	// == METHODS ==
public:
	explicit DefaultNoise(const QImage &t_img,
						  const unsigned int &t_noiseLvl = 0,
						  const int &t_noiseAmp = 0,
						  QObject *parent = 0);

	~DefaultNoise();

	virtual QImage GetNoisedImage() = 0;

protected:
	virtual QList<int> GenerateNoise() = 0;

private:
	void CreateImgNoiseMap();

signals:
	void SignalProcProgressPrc(int t_progress);
};

#endif // DEFAULTNOISE_H
