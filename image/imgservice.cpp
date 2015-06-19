#include "imgservice.h"

#include <time.h>
#include <math.h>

#include <QColor>
#include <QDebug>

const double MIN_SD = 0.00001;

ImgService::ImgService(QObject *parent) :
    QObject(parent)
{
}

// Transform color image to gray image
// @input:
// - t_img - not empty image
// @output:
// QImage - grayscaled copy of input image. Or empty image in case of error
QImage ImgService::ColorImgToGray(const QImage &t_img)
{
    if ( t_img.isNull() )
    {
        qDebug() << __func__ << "Invalid arguments";
        return QImage();
    }

    int width = t_img.width();
    int height = t_img.height();
    QImage grayImg(width, height, QImage::Format_RGB32);

    int onePercent = width / 100;
    int progressPrc = 0;
    int counter = 0;

    for (int wdt = 0; wdt < width; ++wdt)
    {
        for (int hgt = 0; hgt < height; ++hgt)
        {
            QColor pixel = t_img.pixel(wdt, hgt);
            double grayPixel = 0.2126 * pixel.red() +
                               0.7152 * pixel.green() +
                               0.0722 * pixel.blue();

            int resultLuminance = (int)floor(grayPixel + 0.5);
            resultLuminance = qMax(resultLuminance, 0);
            resultLuminance = qMin(resultLuminance, 255);

            grayImg.setPixel(wdt,
                             hgt,
                             qRgb(resultLuminance, resultLuminance, resultLuminance));
        }

        ++counter;
        if ( counter == onePercent )
        {
            counter = 0;
            ++progressPrc;
            emit SignalProgressPrc(progressPrc);
        }
    }

    return grayImg;
}

// Calc Standart Deviation (SD) between two images of the same size
// @input:
// - t_firstImg - not empty image
// - t_secondImg - not empty image with size equal to first image size
// @output:
// - double - result SD. In case of error function will return 0
double ImgService::CalcImgsSD(const QImage &t_firstImg, const QImage &t_secondImg)
{
    double sd = 0.0;
    if ( t_firstImg.isNull() || t_firstImg.size() != t_secondImg.size() )
    {
        qDebug() << __func__ << "Invalid arguments";
        return sd;
    }

    int imgWdt = t_firstImg.width();
    int imgHgt = t_firstImg.height();

    int onePercent = ( imgWdt * imgHgt )/100;
    int progressPrc = 0;
    int counter = 0;

    for (int wdt = 0; wdt < imgWdt; ++wdt)
    {
        for (int hgt = 0; hgt < imgHgt; ++hgt)
        {
            QColor pixelFirst = t_firstImg.pixel(wdt, hgt);
            QColor pixelSecond = t_secondImg.pixel(wdt, hgt);

            // get square of difference between red, green and blue channels of
            // pixels
            double diffRed = pow((pixelFirst.red() - pixelSecond.red()), 2);
            double diffGreen =
                    pow((pixelFirst.green() - pixelSecond.green()), 2);
            double diffBlue = pow((pixelFirst.blue() - pixelSecond.blue()), 2);

            // sum all squares of diffs
            sd += diffRed + diffGreen + diffBlue;

            ++counter;
            if ( counter == onePercent )
            {
                counter = 0;
                ++progressPrc;
                emit SignalProgressPrc(progressPrc);
            }
        }
    }

    sd /= imgWdt * imgHgt;
    if (sd < MIN_SD)
    {
        sd = 0.0;
    }
    else
    {
        // get root of SD
        sd = pow(sd, 0.5);
    }

    return sd;
}
