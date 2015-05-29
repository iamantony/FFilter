#include "masks/mask.h"

#include <QDebug>

Mask::Mask(const unsigned int t_rows, const unsigned int t_cols) :
    m_rows(t_rows), m_cols(t_cols), m_maskPixels(m_rows * m_cols)
{
    if ( false == m_maskPixels.isEmpty() )
    {
        SetCentralPixel(0, 0);
    }
}

// Does mask have pixels
// @output:
// - bool - True if there are no pixels, False otherwise
bool Mask::IsEmpty() const
{
    return m_maskPixels.isEmpty();
}

// Set position of central pixel
// @input:
// - t_row - row of central pixel
// - t_col - column of central pixel
// @output:
// - bool - True if central pixel set, False otherwise
bool Mask::SetCentralPixel(const unsigned int &t_row, const unsigned int &t_col)
{
    if ( IsIndexValid( GetPixelIndex(t_row, t_col) ) )
    {
        m_centralPixelRow = t_row;
        m_centralPixelCol = t_col;

        return true;
    }

    return false;
}

// Get index of pixel in pixels container
// @input:
// - t_row - row of pixel
// - t_col - column of pixel
// @output:
// - int - index of pixel
int Mask::GetPixelIndex(const unsigned int &t_row,
                        const unsigned int &t_col) const
{
    return (t_row * m_cols) + t_col;
}

// Check if index of pixel is valid
// @input:
// - t_index - index of pixel
// @output:
// - bool - True if index if valid, False otherwise
bool Mask::IsIndexValid(const unsigned int &t_index) const
{
    return t_index < static_cast<unsigned int>( m_maskPixels.size() );
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

    if ( t_rows == m_rows && t_cols == m_cols )
    {
        return true;
    }

    if ( m_maskPixels.isEmpty() )
    {
        m_maskPixels.resize( t_rows * t_cols );
        SetCentralPixel(0, 0);
    }
    else
    {
        m_maskPixels.resize( t_rows * m_cols );

        if ( t_cols < m_cols )
        {
//            for ( unsigned int copyTo = t_cols, unsigned int copyFrom = ; i < t_rows * t_cols )
//            {

//            }
        }
        else if ( m_cols < t_cols )
        {

        }
    }

    return true;
}

int Mask::GetCentralPixelIndex() const
{
    return 0;
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
