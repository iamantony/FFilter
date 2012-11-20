#ifndef IMGHANDLER_H
#define IMGHANDLER_H

#include <QObject>
#include <QImage>
#include <QMap>
#include "imgservice.h"
#include "FILTERS/powerfilter.h"
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
	unsigned int m_noiseLvlPercent;
	ImageMode::ImgMode m_imgMode;
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

private:
	// Set (save) image in memory
	void SetImg(QImage t_img, const int &t_imgType);

signals:
	void SignalUIProgrBarValue(int t_value);
	void SignalUIResetProgrBar();
	void SignalUISetSKO(double t_sko);

public slots:
	void SlotProcProgressPrc(int t_value);

	void SlotAggrOpTypeChanged(AggregOperatorType::AggrOpType t_type);
	void SlotAggrOpPowerChanged(double t_power);
	void SlotAggrOpFuncChanged(AggregOperatorFunc::AggrOpFunc t_func);
};

#endif // IMGHANDLER_H
