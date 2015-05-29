#include "imghandler.h"

#include "common/common.h"

ImgHandler::ImgHandler(QObject *parent) :
    QObject(parent)
{
    m_imgMode = Image::GRAYSCALE;
}

void ImgHandler::SetOriginalImg(QImage t_img)
{
    SetImg(t_img, ORIGINAL_IMG);
}

void ImgHandler::SetTargetImg(QImage t_img)
{
    SetImg(t_img, TARGET_IMG);
}

// Set (save) image in memory
void ImgHandler::SetImg(QImage t_img, const int &t_imgType)
{
    if ( (true == t_img.isNull()) ||
         ( (ORIGINAL_IMG != t_imgType) &&
           (TARGET_IMG != t_imgType) ) )
    {
        qDebug() << "SetImg(): Error - invalid arguments";
        return;
    }

    // If app in grayscale mode and image is color, we need to transform it to grayscale
    if ( (Image::GRAYSCALE == m_imgMode) && (false == t_img.isGrayscale()) )
    {
        ImgService imgService;
        connect(&imgService, SIGNAL(SignalProcProgressPrc(int)), this, SLOT(SlotProcProgressPrc(int)));

        QImage grayImg = imgService.TransColorImgToGrayImg(t_img);
        if ( true == grayImg.isNull() )
        {
            qDebug() << "SetImg(): Error - transformation to grayscale image failed";
            return;
        }

        m_imgMass[t_imgType] = grayImg;
    }
    else
    {
        m_imgMass[t_imgType] = t_img;
    }

    emit SignalUIResetProgrBar();
}

QImage ImgHandler::GetOriginalImg()
{
    QImage origImg = m_imgMass[ORIGINAL_IMG];
    return origImg;
}

QImage ImgHandler::GetTargetImg()
{
    QImage targImg = m_imgMass[TARGET_IMG];
    return targImg;
}

void ImgHandler::SetImgMode(Image::Mode t_mode)
{
    m_imgMode = t_mode;
}

void ImgHandler::SetNoiseLevelPrc(int t_noiseLvlPrc)
{
    m_noise.SetNoiseLevel( (unsigned int)t_noiseLvlPrc );
}

// Apply noise to original image and save result as target image
QImage ImgHandler::GetNoisyImg()
{
    if ( true == m_imgMass[ORIGINAL_IMG].isNull() )
    {
        QImage nullImg;
        return nullImg;
    }

    // Set connection for progress bar (on main window)
    connect(&m_noise, SIGNAL(SignalProcProgressPrc(int)), this, SLOT(SlotProcProgressPrc(int)));

    QImage sourceImg = m_imgMass[ORIGINAL_IMG];
    QImage noisyImg = m_noise.SetNoiseToImg(sourceImg);

    // Process ended, so we no more need connection with progress bar
    m_noise.disconnect(SIGNAL(SignalProcProgressPrc(int)));

    if ( true == noisyImg.isNull() )
    {
        return m_imgMass[ORIGINAL_IMG];
    }

    m_imgMass[TARGET_IMG] = noisyImg;
    return noisyImg;
}

// Calc SKO between original and target (noised) images
double ImgHandler::GetImgsSKO()
{
    ImgService imgService;
    connect(&imgService, SIGNAL(SignalProcProgressPrc(int)), this, SLOT(SlotProcProgressPrc(int)));

    double sko =  imgService.CalcImgsSKO(m_imgMass[ORIGINAL_IMG], m_imgMass[TARGET_IMG]);
    if ( ERROR == sko )
    {
        sko = 0;
    }

    emit SignalUISetSKO(sko);
    return sko;
}

// Start filtration
QImage ImgHandler::PerfFiltration()
{
    PowerFilter filter;
    filter.Init(m_mask, m_aggrOpHandler.GetAggrOperator());
    connect(&filter, SIGNAL(SignalProcProgressPrc(int)), this, SLOT(SlotProcProgressPrc(int)));
//    connect(&filter, SIGNAL(SignalFiltrationFinished()), &m_mask, SLOT(SlotFiltrationDone()));

    QImage filteredImg = filter.FilterImg(m_imgMass[TARGET_IMG]);
    if ( true == filteredImg.isNull() )
    {
        // Filtration failed. Return noised image.
        filteredImg = m_imgMass[TARGET_IMG];
    }
    else
    {
        // Filtration successed. Update parameters.
        m_imgMass[TARGET_IMG] = filteredImg;
        GetImgsSKO();
    }

    return filteredImg;
}

AggregOperator::Type::Type ImgHandler::GetAggrOpType()
{
    return m_aggrOpHandler.GetAggrOpType();
}

double ImgHandler::GetAggrOpPower()
{
    return m_aggrOpHandler.GetAggrOpPower();
}

AggregOperator::Func::Type ImgHandler::GetAggrOpFunc()
{
    return m_aggrOpHandler.GetAggrOpFunc();
}

Noise::Type ImgHandler::GetNoiseType()
{
    return m_noise.GetNoiseType();
}

int ImgHandler::GetNoiseAmp()
{
    return m_noise.GetNoiseAmplitude();
}

void ImgHandler::SlotProcProgressPrc(int t_value)
{
    int progressValue = ERROR;

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

void ImgHandler::SlotAggrOpTypeChanged(AggregOperator::Type::Type t_type)
{
    m_aggrOpHandler.SlotSetAggrOpType(t_type);
}

void ImgHandler::SlotAggrOpPowerChanged(double t_power)
{
    m_aggrOpHandler.SlotSetAggrOpPower(t_power);
}

void ImgHandler::SlotAggrOpFuncChanged(AggregOperator::Func::Type t_func)
{
    m_aggrOpHandler.SlotSetAggrOpFunc(t_func);
}

void ImgHandler::SlotTransmitMask()
{
//    emit SignalSendMask(m_mask.GetMaskStructure());
}

//void ImgHandler::SlotRecieveMask(QMap<unsigned int, QList<Mask::MasksPixel> > t_mask)
//{
//    if ( true == t_mask.isEmpty() )
//    {
//        qDebug() << "ImgHandler::SlotRecieveMask(): Error - invalid arguments";
//        return;
//    }

//    m_mask.SetMaskStructure(t_mask);
//}

void ImgHandler::SlotRecieveNoiseType(Noise::Type t_type)
{
    m_noise.SetNoiseType(t_type);
}

void ImgHandler::SlotRecieveNoiseAmp(int t_amp)
{
    m_noise.SetNoiseAmplitude(t_amp);
}
