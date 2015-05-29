#ifndef IMGHANDLER_H
#define IMGHANDLER_H

#include <QObject>
#include <QImage>
#include <QMap>
#include <QSharedPointer>

#include "imgservice.h"
#include "noise/noisegenerator.h"
#include "filters/powerfilter.h"
#include "masks/mask.h"
#include "noise/noise.h"
#include "aggreg_operators/aggrophandler.h"
#include "image/image.h"

#define ORIGINAL_IMG 0
#define TARGET_IMG 1

class ImgHandler : public QObject
{
    Q_OBJECT

    // == METHODS ==
public:
    explicit ImgHandler(QObject *parent = 0);

    void SetOriginalImg(QImage t_img);
    void SetTargetImg(QImage t_img);
    QImage GetOriginalImg();
    QImage GetTargetImg();

    void SetImgMode(Image::Mode t_mode);
    void SetNoiseLevelPrc(int t_noiseLvlPrc);
    // Apply noise to original image and save result as target image
    QImage GetNoisyImg();
    // Calc SKO between original and target (noised) images
    double GetImgsSKO();
    // Start filtration
    QImage PerfFiltration();

    AggregOperator::Type::Type GetAggrOpType();
    double GetAggrOpPower();
    AggregOperator::Func::Type GetAggrOpFunc();

    Noise::Type GetNoiseType();
    int GetNoiseAmp();

private:
    // Set (save) image in memory
    void SetImg(QImage t_img, const int &t_imgType);

signals:
    void SignalUIProgrBarValue(int t_value);
    void SignalUIResetProgrBar();
    void SignalUISetSKO(double t_sko);
//    void SignalSendMask(QMap<unsigned int,QList<Mask::MasksPixel> > t_mask);

public slots:
    void SlotProcProgressPrc(int t_value);
    void SlotAggrOpTypeChanged(AggregOperator::Type::Type t_type);
    void SlotAggrOpPowerChanged(double t_power);
    void SlotAggrOpFuncChanged(AggregOperator::Func::Type t_func);
    void SlotTransmitMask();
//    void SlotRecieveMask(QMap<unsigned int, QList<Mask::MasksPixel> > t_mask);
    void SlotRecieveNoiseType(Noise::Type t_type);
    void SlotRecieveNoiseAmp(int t_amp);

    // == DATA ==
private:
    QImage m_imgMass[2];
    Image::Mode m_imgMode;
    NoiseGenerator m_noise;
    QSharedPointer<Mask> m_mask;
    AggrOpHandler m_aggrOpHandler;
};

#endif // IMGHANDLER_H
