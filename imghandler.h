/* === This file is part of FFilter ===
 *
 *	Copyright 2012, Antony Cherepanov <antony.cherepanov@gmail.com>
 *
 *	FFilter is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	FFilter is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with FFilter. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef IMGHANDLER_H
#define IMGHANDLER_H

#include <QObject>
#include <QImage>
#include <QMap>
#include "imgservice.h"
#include "NOISE/noisegenerator.h"
#include "FILTERS/powerfilter.h"
#include "MASKS/maskstructure.h"
#include "AGGR_OP/aggrophandler.h"
#include "DEFINES/common.h"
#include "DEFINES/enums.h"

#define ORIGINAL_IMG 0
#define TARGET_IMG 1

class ImgHandler : public QObject
{
	Q_OBJECT

	// == DATA ==
private:
	QImage m_imgMass[2];
	ImageMode::ImgMode m_imgMode;
	NoiseGenerator m_noise;
	MaskStructure m_maskStruct;
	AggrOpHandler m_aggrOpHandler;

	// == METHODS ==
public:
	explicit ImgHandler(QObject *parent = 0);

	void SetOriginalImg(QImage t_img);
	void SetTargetImg(QImage t_img);
	QImage GetOriginalImg();
	QImage GetTargetImg();

	void SetImgMode(ImageMode::ImgMode t_mode);
	void SetNoiseLevelPrc(int t_noiseLvlPrc);
	// Apply noise to original image and save result as target image
	QImage GetNoisyImg();
	// Calc SKO between original and target (noised) images
	double GetImgsSKO();
	// Start filtration
	QImage PerfFiltration();

	AggregOperatorType::AggrOpType GetAggrOpType();
	double GetAggrOpPower();
	AggregOperatorFunc::AggrOpFunc GetAggrOpFunc();

	Noise::NoiseType GetNoiseType();
	int GetNoiseAmp();

private:
	// Set (save) image in memory
	void SetImg(QImage t_img, const int &t_imgType);

signals:
	void SignalUIProgrBarValue(int t_value);
	void SignalUIResetProgrBar();
	void SignalUISetSKO(double t_sko);
	void SignalSendMask(QMap<unsigned int,QList<Mask::MasksPixel> > t_mask);

public slots:
	void SlotProcProgressPrc(int t_value);
	void SlotAggrOpTypeChanged(AggregOperatorType::AggrOpType t_type);
	void SlotAggrOpPowerChanged(double t_power);
	void SlotAggrOpFuncChanged(AggregOperatorFunc::AggrOpFunc t_func);
	void SlotTransmitMask();
	void SlotRecieveMask(QMap<unsigned int, QList<Mask::MasksPixel> > t_mask);
	void SlotRecieveNoiseType(Noise::NoiseType t_type);
	void SlotRecieveNoiseAmp(int t_amp);
};

#endif // IMGHANDLER_H
