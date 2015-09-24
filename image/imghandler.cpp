#include "imghandler.h"

#include <QDebug>

#include "image/imgservice.h"
#include "filters/powerfilter.h"

ImgHandler::ImgHandler(QObject *parent) :
    QObject(parent), m_mask(new Mask())
{
    m_imgMode = Image::Mode::GRAYSCALE;
}

// Set original image
// @input:
// - t_img - valid image
// @output:
// - bool - True if image was set, False otherwise
bool ImgHandler::SetOriginalImg(const QImage &t_img)
{
    if ( t_img.isNull() )
    {
        qDebug() << __FUNCTION__ << "Invalid arguments";
        return false;
    }

    if ( Image::Mode::GRAYSCALE == m_imgMode && false == t_img.isGrayscale() )
    {
        ImgService imgService;
        QImage grayImg = imgService.ColorImgToGray(t_img);
        if ( grayImg.isNull() )
        {
            qDebug() << __FUNCTION__ << "Transformation to grayscale image failed";
            return false;
        }

        m_originalImg = grayImg;
    }
    else
    {
        m_originalImg = t_img;
    }

    m_targetImg = m_originalImg;

    return true;
}

// Get original image
// @output:
// - QImage - current original image
QImage ImgHandler::GetOriginalImg()
{
    return m_originalImg;
}

// Get target image
// @output:
// - QImage - current target image
QImage ImgHandler::GetTargetImg()
{
    return m_targetImg;
}

// Set image mode
// @input:
// - t_mode - set image mode
void ImgHandler::SetImgMode(const Image::Mode &t_mode)
{
    m_imgMode = t_mode;
}

// Set percent of noise level
// @input:
// - t_noiseLvlPrc - percent of noise level
void ImgHandler::SetNoiseLevelPrc(const unsigned int t_noiseLvlPrc)
{
    m_noise.SetNoiseLevel( t_noiseLvlPrc );
}

// Apply noise to original image, set it as target image and then return it
// @output:
// - QImage - noised image. Could be Null if process failed
QImage ImgHandler::GetNoisyImg()
{
    // Set connection for progress bar (on main window)
    connect(&m_noise, SIGNAL(SignalProgressPrc(int)),
            this, SLOT(SlotProgressPrc(int)));

    QImage noisyImg = m_noise.NoiseImage( m_originalImg );

    // Process ended, so we no more need connection with progress bar
    m_noise.disconnect(SIGNAL(SignalProgressPrc(int)));

    if ( false == noisyImg.isNull() )
    {
        m_targetImg = noisyImg;
    }

    return m_targetImg;
}

// Calc SD between original and target images
// @output:
// - double - result SD
double ImgHandler::CalcImgsSD()
{
    ImgService imgService;
    connect(&imgService, SIGNAL(SignalProgressPrc(int)),
            this, SLOT(SlotProgressPrc(int)));

    double sd =  imgService.CalcImgsSD(m_originalImg, m_targetImg);

    imgService.disconnect(SIGNAL(SignalProgressPrc(int)));

    emit SignalUISetSD(sd);

    return sd;
}

// Start filtration of target image
// @output:
// - QImage - result filtered target image
QImage ImgHandler::FilterTargetImg()
{
    PowerFilter filter;
    if ( false == filter.Init(m_mask, m_aggrOpHandler.GetAggrOperator()) )
    {
        qDebug() << __FUNCTION__ << "Failed to init filter";
        return QImage();
    }

    connect(&filter, SIGNAL(SignalProgressPrc(int)),
            this, SLOT(SlotProgressPrc(int)));

    QImage filteredImg = filter.FilterImg(m_targetImg);

    filter.disconnect(SIGNAL(SignalProgressPrc(int)));

    if ( false == filteredImg.isNull() )
    {
        m_targetImg = filteredImg;
        CalcImgsSD();
    }

    return m_targetImg;
}

// Get current aggregation operator type
AggregOperator::Type ImgHandler::GetAggrOpType()
{
    return m_aggrOpHandler.GetAggrOpType();
}

// Get current power of aggregation operator
double ImgHandler::GetAggrOpPower()
{
    return m_aggrOpHandler.GetAggrOpPower();
}

// Get current function type of aggregation operator
AggregOperator::Func ImgHandler::GetAggrOpFunc()
{
    return m_aggrOpHandler.GetAggrOpFunc();
}

// Get current noise type
Noise::Type ImgHandler::GetNoiseType()
{
    return m_noise.GetNoiseType();
}

// Get current noise amplitude
int ImgHandler::GetNoiseAmp()
{
    return m_noise.GetNoiseAmplitude();
}

// Get pointer to mask
QSharedPointer<Mask> ImgHandler::GetMask()
{
    return m_mask;
}

// Slot for transmitting process progress (0 - 100 percents)
void ImgHandler::SlotProgressPrc(int t_value)
{
    int progressValue = 0;

    if ( t_value < 0 )
    {
        progressValue = 0;
    }
    else if ( 100 < t_value )
    {
        progressValue = 100;
    }
    else
    {
        progressValue = t_value;
    }

    emit SignalUIProgrBarValue(progressValue);
}

// Slot to change aggregation operator type
void ImgHandler::SlotAggrOpTypeChanged(AggregOperator::Type t_type)
{
    m_aggrOpHandler.SlotSetAggrOpType(t_type);
}

// Slot to change aggregation operator power
void ImgHandler::SlotAggrOpPowerChanged(double t_power)
{
    m_aggrOpHandler.SlotSetAggrOpPower(t_power);
}

// Slot to change function type of aggregation operator
void ImgHandler::SlotAggrOpFuncChanged(AggregOperator::Func t_func)
{
    m_aggrOpHandler.SlotSetAggrOpFunc(t_func);
}

// Slot to change noise type
void ImgHandler::SlotRecieveNoiseType(Noise::Type t_type)
{
    m_noise.SetNoiseType(t_type);
}

// Slot to change noise amplitude
void ImgHandler::SlotRecieveNoiseAmp(int t_amp)
{
    m_noise.SetNoiseAmplitude(t_amp);
}
