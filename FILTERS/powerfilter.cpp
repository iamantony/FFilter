#include "powerfilter.h"

#include <algorithm>

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
    int imgW = t_img.width();
    int imgH = t_img.height();

    const int onePrc = imgW / 100;
    int progressPrc = 0;
    int counter = 0;

    // For each pixel in image
    for (int w = 0; w < imgW; ++w)
    {
        for (int h = 0; h < imgH; ++h)
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
QList<double> PowerFilter::FormMaskPixels(const QImage& t_img,
                                          const int& t_width,
                                          const int& t_height)
{
    if ( t_img.isNull() ||
         m_mask.isNull() ||
         t_width < 0 ||
         t_height < 0 ||
         t_img.width() <= t_width ||
         t_img.height() <= t_height )
    {
        qDebug() << __FUNCTION__ << "Error - invalid settings";
        return QList<double>();
    }

    QList<double> pixels;
    const int maskRows = m_mask->GetRowsNum();
    const int maskCols = m_mask->GetColsNum();
    const int centralPixRow = m_mask->GetCentralPixelRow();
    const int centralPixCol = m_mask->GetCentralPixelCol();
    for (int row = 0; row < maskRows; ++row)
    {
        for (int col = 0; col < maskCols; ++col)
        {
            if ( false == m_mask->IsPixelEnabled(row, col) )
            {
                continue;
            }

            int widthOffset = col - centralPixCol;
            int heightOffset = row - centralPixRow;
            int pixWidth = std::min(std::max(0, t_width + widthOffset),
                                    t_img.width() - 1);

            int pixHeight = std::min(std::max(0, t_height + heightOffset),
                                     t_img.height() - 1);

            pixels << t_img.pixel(pixWidth, pixHeight) *
                      m_mask->GetPixelWeight(row, col);
        }
    }

    return pixels;
}
