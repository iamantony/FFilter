#include "imghandler.h"

#include <QDebug>

#include "filters/powerfilter.h"

ImgHandler::ImgHandler(QObject *parent) :
    QObject(parent), m_mask(new Mask())
{
    m_imgMode = Image::GRAYSCALE;
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
        qDebug() << __func__ << "Invalid arguments";
        return false;
    }

    if ( Image::GRAYSCALE == m_imgMode && false == t_img.isGrayscale() )
    {
        ImgService imgService;
        QImage grayImg = imgService.TransColorImgToGrayImg(t_img);
        if ( grayImg.isNull() )
        {
            qDebug() << __func__ << "Transformation to grayscale image failed";
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
    connect(&m_noise, SIGNAL(SignalProcProgressPrc(int)),
            this, SLOT(SlotProcProgressPrc(int)));

    QImage noisyImg = m_noise.SetNoiseToImg( m_originalImg );

    // Process ended, so we no more need connection with progress bar
    m_noise.disconnect(SIGNAL(SignalProcProgressPrc(int)));

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
    connect(&imgService, SIGNAL(SignalProcProgressPrc(int)),
            this, SLOT(SlotProcProgressPrc(int)));

    double sd =  imgService.CalcImgsSD(m_originalImg, m_targetImg);

    imgService.disconnect(SIGNAL(SignalProcProgressPrc(int)));

    emit SignalUISetSD(sd);

    return sd;
}

// Start filtration of target image
// @output:
// - QImage - result filtered target image
QImage ImgHandler::FilterTargetImg()
{
    PowerFilter filter;
    filter.Init(m_mask, m_aggrOpHandler.GetAggrOperator());
    connect(&filter, SIGNAL(SignalProcProgressPrc(int)),
            this, SLOT(SlotProcProgressPrc(int)));

    QImage filteredImg = filter.FilterImg(m_targetImg);

    filter.disconnect(SIGNAL(SignalProcProgressPrc(int)));

    if ( false == filteredImg.isNull() )
    {
        m_targetImg = filteredImg;
        CalcImgsSD();
    }

    return m_targetImg;
}

// Get current aggregation operator type
AggregOperator::Type::Type ImgHandler::GetAggrOpType()
{
    return m_aggrOpHandler.GetAggrOpType();
}

// Get current power of aggregation operator
double ImgHandler::GetAggrOpPower()
{
    return m_aggrOpHandler.GetAggrOpPower();
}

// Get current function type of aggregation operator
AggregOperator::Func::Type ImgHandler::GetAggrOpFunc()
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

// Slot for transmitting process progress (0 - 100 percents)
void ImgHandler::SlotProcProgressPrc(int t_value)
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
void ImgHandler::SlotAggrOpTypeChanged(AggregOperator::Type::Type t_type)
{
    m_aggrOpHandler.SlotSetAggrOpType(t_type);
}

// Slot to change aggregation operator power
void ImgHandler::SlotAggrOpPowerChanged(double t_power)
{
    m_aggrOpHandler.SlotSetAggrOpPower(t_power);
}

// Slot to change function type of aggregation operator
void ImgHandler::SlotAggrOpFuncChanged(AggregOperator::Func::Type t_func)
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
