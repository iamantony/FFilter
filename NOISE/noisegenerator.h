#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H

#include <QObject>
#include <QDebug>
#include "DEFINES/common.h"
#include "DEFINES/enums.h"

class NoiseGenerator : public QObject
{
	Q_OBJECT

	// == DATA ==
private:
	Noise::NoiseType m_noiseType;
	int m_noiseAmp;
	unsigned int m_noiseLvlPercent;

	// == METHODS ==
public:
	explicit NoiseGenerator(QObject *parent = 0);

	void SetNoiseType(Noise::NoiseType t_type);
	Noise::NoiseType GetNoiseType();
	void SetNoiseAmplitude(const int &t_amp);
	int GetNoiseAmplitude();
	void SetNoiseLevel(const unsigned int &t_level);

signals:

public slots:

};

#endif // NOISEGENERATOR_H
