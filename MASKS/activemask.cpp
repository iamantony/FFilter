#include "activemask.h"

ActiveMask::ActiveMask(QList<Mask::MasksPixel> t_mask, QObject *parent) :
    QObject(parent)
{
    if ( true == t_mask.isEmpty() )
    {
        qDebug() << "ActiveMask(): Error - invalid arguments";
    }

    m_mask.clear();
    m_mask = t_mask;
}

// Get list of active pixel in mask for defined pixel from image t_img
QList<long double> ActiveMask::FormPixelMask(const QImage &t_img,
                                                const unsigned int &t_pixelCoordX,
                                                const unsigned int &t_pixelCoordY)
{
    if ( true == t_img.isNull() )
    {
        qDebug() << "ActiveMask::FormPixelMask(): Error - invalid arguments";
        QList<long double> emptyList;
        return emptyList;
    }

    QList<long double> pixelsInMask;

    for (int i = 0; i < m_mask.size(); i++)
    {
        m_maskPixelCoordX = t_pixelCoordX;
        m_maskPixelCoordY = t_pixelCoordY;

        if ( false == m_mask.at(i).isCentral )
        {
            m_maskPixelCoordX += m_mask.at(i).posX;
            m_maskPixelCoordY += m_mask.at(i).posY;
        }

        if ( false == t_img.valid(m_maskPixelCoordX, m_maskPixelCoordY) )
        {
            continue;
        }

        m_pixel = t_img.pixel(m_maskPixelCoordX, m_maskPixelCoordY);

        m_weightedPixel = m_mask.at(i).weight * (long double)m_pixel.red();

        pixelsInMask.append(m_weightedPixel);
    }

    return pixelsInMask;
}
