#include "masks/mask.h"

#include <QDebug>

Mask::Mask(const unsigned int t_rows, const unsigned int t_cols) :
    m_rows(t_rows), m_cols(t_cols), m_maskPixels(m_rows * m_cols)
{
    if ( false == m_maskPixels.isEmpty() )
    {
        m_maskPixels.front().SetCentral(true);
    }
}

// Set size of the mask
bool Mask::SetMaskSize(const unsigned int &t_rows, const unsigned int &t_cols)
{
    if ( ResizeMask(t_rows, t_cols) )
    {
        m_rows = t_rows;
        m_cols = t_cols;
        return true;
    }

    qDebug() << __func__ << "Failed to set mask size";

    return false;
}

bool Mask::ResizeMask(const unsigned int &t_rows, const unsigned int &t_cols)
{
    if ( 0 == t_rows || 0 == t_cols )
    {
        qDebug() << __func__ << "Invalid size values";
        return false;
    }

    if ( m_maskPixels.isEmpty() )
    {
        m_maskPixels.resize( t_rows * t_cols );
        m_maskPixels.front().SetCentral(true);
    }
    else
    {

    }

    return true;
}

int Mask::GetPixelIndex(const unsigned int &t_row,
                        const unsigned int &t_col) const
{
    return (t_row * m_cols) + t_col;
}

int Mask::GetCentralPixelIndex() const
{
    return 0;
}

bool Mask::IsEmpty() const
{
    return m_maskPixels.isEmpty();
}

// Check if mask structure is valid
bool Mask::CheckMask()
{
//    unsigned int numOfCentralPixels = 0;
//    unsigned int numOfActivePixels = 0;

//    QList<Mask::MasksPixel> allPixels;
//    QList<unsigned int> lines = t_mask.keys();
//    for (int i = 0; i < lines.size(); i++)
//    {
//        unsigned int key = lines.at(i);
//        allPixels.append(t_mask.value(key));
//    }

//    // Get statistic
//    for (int pix = 0; pix < allPixels.size(); pix++)
//    {
//        if ( true == allPixels.at(pix).isCentral )
//        {
//            numOfCentralPixels++;
//        }

//        if ( true == allPixels.at(pix).isEnabled )
//        {
//            numOfActivePixels++;
//        }
//    }

//    // Check the Rules:
//    if ( NUM_OF_CENTRAL_PIXELS != numOfCentralPixels )
//    {
//        qDebug() << "Mask::CheckMask(): Rule of number of central pixels in mask doesn't hold";
////		QMessageBox::warning(this, "Filter Mask Error", "Mask must have only one central pixel. Default mask set");
//        return false;
//    }

//    if ( numOfActivePixels < MIN_NUM_OF_ACTIVE_PIXELS )
//    {
//        qDebug() << "Mask::CheckMask(): Rule of minimum number of active pixels in mask doesn't hold";
////		QMessageBox::warning(this, "Filter Mask Error", "Mask must have at least one active pixel. Default mask set");
//        return false;
//    }

//    // TODO: send warning signal to main window

    return true;
}
