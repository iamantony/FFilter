#include "powerfilter.h"

#include <QColor>
#include <QDebug>

#include "common/common.h"

PowerFilter::PowerFilter(QObject *parent) :
    QObject(parent)
{
    SetDefaults();
}

PowerFilter::~PowerFilter()
{
    SetDefaults();
}

void PowerFilter::SetDefaults()
{
    m_aggregOperator = NULL;
}

void PowerFilter::Init(QSharedPointer<Mask> t_mask, DefaultAggregOperator *t_aggrOp)
{
    if ( (NULL == t_mask) || (NULL == t_aggrOp) )
    {
        qDebug() << "PowerFilter::Init(): Error - invalid arguments";
        return;
    }

    m_mask = t_mask;
    m_aggregOperator = t_aggrOp;
}

QImage PowerFilter::FilterImg(const QImage &t_noisyImg)
{
    if ( (NULL == m_mask) || (NULL == m_aggregOperator) )
    {
        qDebug() << "PowerFilter::FilterImg(): Error - filter is not initialised";
        return t_noisyImg;
    }

    if ( true == t_noisyImg.isNull() )
    {
        qDebug() << "PowerFilter::FilterImg(): Error - invalid arguments";
        return t_noisyImg;
    }

    QImage filteredImg = t_noisyImg;
    unsigned int imgW = (unsigned int)t_noisyImg.width();
    unsigned int imgH = (unsigned int)t_noisyImg.height();

//    QList<long double> pixelsInMask;
//    int resultLum = 0;
//    QRgb newPixel;

    const int onePercent = imgW/100;
    int progressPrc = 0;
    int counter = 0;

    // For each pixel in image
    for (unsigned int w = 0; w < imgW; w++)
    {
        for (unsigned int h = 0; h < imgH; h++)
        {
//            // Get list of pixels in mask
//            pixelsInMask.clear();
//            pixelsInMask = m_mask->FormPixelMask(t_noisyImg, w, h);
//            resultLum = m_aggregOperator->GetWorthlyValue(pixelsInMask);
//            if ( ERROR != resultLum )
//            {
//                newPixel = qRgb(resultLum, resultLum, resultLum);
//                filteredImg.setPixel(w, h, newPixel);
//            }
        }

        counter++;
        if ( counter == onePercent )
        {
            counter = 0;
            progressPrc++;
            emit SignalProgressPrc(progressPrc);
        }
    }

    emit SignalFiltrationFinished();

    return filteredImg;
}
