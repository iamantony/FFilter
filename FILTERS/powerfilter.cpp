#include "powerfilter.h"

#include <QImage>
#include <QColor>
#include <QDebug>

PowerFilter::PowerFilter(QObject *parent) :
    QObject(parent)
{
}

// Initialize
// @input:
// - t_mask - valid pointer to Mask object
// - t_aggrOp - valid pointer to DefaultAggregOperator object
// @output:
// - bool - True if initialization was successful, False otherwise
bool PowerFilter::Init(QSharedPointer<Mask> t_mask,
                       QSharedPointer<DefaultAggregOperator> t_aggrOp)
{
    if ( t_mask.isNull() || t_aggrOp.isNull() )
    {
        qDebug() << __FUNCTION__ << "Error - invalid arguments";
        return false;
    }

    m_mask = t_mask;
    m_aggregOperator = t_aggrOp;

    return true;
}

// Perform image filtration
// @input:
// - t_img - valid image that should be filtered from noise
// @outpu:
// - QImage - result filtered image. Function will return empty image if
// there was an error during filtration process
QImage PowerFilter::FilterImg(const QImage &t_img)
{
    if ( m_mask.isNull() || m_aggregOperator.isNull() )
    {
        qDebug() << __FUNCTION__ << "Error - filter is not initialised";
        return QImage();
    }

    if ( t_img.isNull() )
    {
        qDebug() << __FUNCTION__ << "Error - invalid arguments";
        return QImage();
    }

    QImage filteredImg(t_img);
    unsigned int imgW = (unsigned int)t_img.width();
    unsigned int imgH = (unsigned int)t_img.height();

    const unsigned int onePrc = imgW / 100;
    unsigned int progressPrc = 0;
    unsigned int counter = 0;

    // For each pixel in image
    for (unsigned int w = 0; w < imgW; ++w)
    {
        for (unsigned int h = 0; h < imgH; ++h)
        {
            // Get list of pixels in mask and calc filtered value of this pixel
            QList<double> pixelsInMask = FormMaskPixels(t_img, w, h);
            int resultPixel = m_aggregOperator->Calc(pixelsInMask);

            QRgb newPixel = qRgb(resultPixel, resultPixel, resultPixel);
            filteredImg.setPixel(w, h, newPixel);
        }

        ++counter;
        if ( counter == onePrc )
        {
            counter = 0;
            ++progressPrc;
            emit SignalProgressPrc(progressPrc);
        }
    }

    emit SignalFiltrationFinished();

    return filteredImg;
}

// Create list of pixels that located in mask
// @input:
// - t_img - image
// - t_width - horizontal position of pixel
// - t_height - vertical position of pixel
// @outpu:
// - QList<double> - list of mask pixels
QList<double> PowerFilter::FormMaskPixels(const QImage& /*t_img*/,
                                          const unsigned int& /*t_width*/,
                                          const unsigned int& /*t_height*/)
{
    return QList<double>();
}
