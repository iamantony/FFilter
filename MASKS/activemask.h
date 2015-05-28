#ifndef ACTIVEMASK_H
#define ACTIVEMASK_H

#include <QObject>
#include <QList>
#include <QImage>
#include <QColor>
#include <QDebug>
#include "activemask.h"
#include "masks/mask.h"

class ActiveMask : public QObject
{
    Q_OBJECT

    // == DATA ==
private:
    QList<Mask::MasksPixel> m_mask;
    QColor m_pixel;
    long double m_weightedPixel;
    int m_maskPixelCoordX;
    int m_maskPixelCoordY;

    // == METHODS ==
public:
    explicit ActiveMask( QList<Mask::MasksPixel> t_mask, QObject *parent = 0);

    // Get list of active pixel in mask for defined pixel from image t_img
    QList<long double> FormPixelMask(const QImage &t_img,
                                     const unsigned int &t_pixelCoordX,
                                     const unsigned int &t_pixelCoordY);


};

#endif // ACTIVEMASK_H
