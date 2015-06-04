#ifndef IMGHANDLER_H
#define IMGHANDLER_H

#include <QObject>
#include <QList>
#include <QImage>
#include <QMap>
#include <QSharedPointer>

#include "imgservice.h"
#include "noise/noisegenerator.h"
#include "masks/mask.h"
#include "noise/noise.h"
#include "aggreg_operators/aggrophandler.h"
#include "image/image.h"

class ImgHandler : public QObject
{
    Q_OBJECT

    // == METHODS ==
public:
    explicit ImgHandler(QObject *parent = 0);

    // Set original image
    bool SetOriginalImg(const QImage &t_img);
    // Get original image
    QImage GetOriginalImg();
    // Get target image
    QImage GetTargetImg();
    // Set image mode
    void SetImgMode(const Image::Mode &t_mode);
    // Set percent of noise level
    void SetNoiseLevelPrc(const unsigned int t_noiseLvlPrc);
    // Apply noise to original image, set it as target image and then return it
    QImage GetNoisyImg();
    // Calc SD between original and target images
    double CalcImgsSD();
    // Start filtration of target image
    QImage FilterTargetImg();
    // Get current aggregation operator type
    AggregOperator::Type::Type GetAggrOpType();
    // Get current power of aggregation operator
    double GetAggrOpPower();
    // Get current function type of aggregation operator
    AggregOperator::Func::Type GetAggrOpFunc();
    // Get current noise type
    Noise::Type GetNoiseType();
    // Get current noise amplitude
    int GetNoiseAmp();
    // Get pointer to mask
    QSharedPointer<Mask> GetMask();

signals:
    void SignalUIProgrBarValue(int t_value);
    void SignalUIResetProgrBar();
    void SignalUISetSD(double t_sko);

public slots:
    // Slot for transmitting process progress (0 - 100 percents)
    void SlotProcProgressPrc(int t_value);
    // Slot to change aggregation operator type
    void SlotAggrOpTypeChanged(AggregOperator::Type::Type t_type);
    // Slot to change aggregation operator power
    void SlotAggrOpPowerChanged(double t_power);
    // Slot to change function type of aggregation operator
    void SlotAggrOpFuncChanged(AggregOperator::Func::Type t_func);
    // Slot to change noise type
    void SlotRecieveNoiseType(Noise::Type t_type);
    // Slot to change noise amplitude
    void SlotRecieveNoiseAmp(int t_amp);

    // == DATA ==
private:
    QImage m_originalImg;
    QImage m_targetImg;
    Image::Mode m_imgMode;
    NoiseGenerator m_noise;
    QSharedPointer<Mask> m_mask;
    AggrOpHandler m_aggrOpHandler;
};

#endif // IMGHANDLER_H
