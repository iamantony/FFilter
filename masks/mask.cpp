#include "masks/mask.h"

#include <QDebug>

Mask::Mask(const int t_rows, const int t_cols)
{
    SetMaskSize(t_rows, t_cols);
}

// Does mask have pixels
// @output:
// - bool - True if there are no pixels, False otherwise
bool Mask::IsEmpty() const
{
    return m_maskPixels.isEmpty();
}

// Check if pixel woth defined coordinates exist
// @input:
// - t_row - row of pixel
// - t_col - column of pixel
// @output:
// - bool - True if pixel exist, False otherwise
bool Mask::IsPixelExist(const int& t_row, const int& t_col) const
{
    return ( t_row < m_maskPixels.size() &&
             t_col < m_maskPixels.first().size() );
}

// Set size of the mask
// @input:
// - t_rows - new number of rows
// - t_cols - new number of columns
void Mask::SetMaskSize(const int& t_rows, const int& t_cols)
{
    ResizeMask(t_rows, t_cols);
}

// Resize mask
// @input:
// - t_rows - new number of rows
// - t_cols - new number of columns
void Mask::ResizeMask(const int& t_rows, const int& t_cols)
{
    if ( t_rows <= 0 || t_cols <= 0 )
    {
        qDebug() << __FUNCTION__ << "Error - Invalid mask size";
        return;
    }

    if ( t_rows == m_maskPixels.size() &&
         t_cols == m_maskPixels.first().size() )
    {
        return;
    }

    bool maskWasEmpty = m_maskPixels.isEmpty();
    m_maskPixels.resize(t_rows);
    for ( int i = 0; i < m_maskPixels.size(); ++i )
    {
        m_maskPixels[i].resize(t_cols);
    }

    if ( maskWasEmpty )
    {
        SetPixelActiveStatus(0, 0, true);
    }

    int centralPixRow = std::min(m_maskPixels.size() - 1, m_centralPixel.y());
    int centralPixCol = std::min(m_maskPixels.first().size() - 1,
                                 m_centralPixel.x());

    SetCentralPixel(centralPixRow, centralPixCol);
}

// Get number of rows in mask
// @output:
// - unsigned int - number of rows in mask
int Mask::GetRowsNum() const
{
    return m_maskPixels.size();
}

// Get number of columns in mask
// @output:
// - unsigned int - number of columns in mask
int Mask::GetColsNum() const
{
    return m_maskPixels.first().size();
}

// Check if pixel enabled
// @input:
// - t_row - row of pixel
// - t_col - column of pixel
// @output:
// - bool - True if pixel enabled, False otherwise
bool Mask::IsPixelEnabled(const int& t_row, const int& t_col) const
{
    if ( false == IsPixelExist(t_row, t_col) )
    {
        qDebug() << __FUNCTION__ << "Invalid pixel index";
        return false;
    }

    return m_maskPixels.at(t_row).at(t_col).IsEnabled();
}

// Enable / disable pixel
// @input:
// - t_row - row of pixel
// - t_col - column of pixel
// - t_isEnabled - pixel status
void Mask::SetPixelActiveStatus(const int& t_row,
                                const int& t_col,
                                const bool& t_isEnabled)
{
    if ( false == IsPixelExist(t_row, t_col) )
    {
        qDebug() << __FUNCTION__ << "Invalid pixel index";
        return;
    }

    m_maskPixels[t_row][t_col].SetEnabled(t_isEnabled);
}

// Get weight of pixel
// @input:
// - t_row - row of pixel
// - t_col - column of pixel
// @output:
// - double - wight of pixel
double Mask::GetPixelWeight(const int& t_row, const int& t_col) const
{
    if ( false == IsPixelExist(t_row, t_col) )
    {
        qDebug() << __FUNCTION__ << "Invalid pixel index";
        return 0.0;
    }

    return m_maskPixels[t_row][t_col].GetWeight();
}

// Set weight of pixel
// @input:
// - t_row - row of pixel
// - t_col - column of pixel
// - t_weight - new weight of pixel
void Mask::SetPixelWeight(const int& t_row,
                          const int& t_col,
                          const double& t_weight)
{
    if ( false == IsPixelExist(t_row, t_col) )
    {
        qDebug() << __FUNCTION__ << "Invalid pixel index";
        return;
    }

    m_maskPixels[t_row][t_col].SetWeight(t_weight);
}

// Get row coordinate of central pixel
// @output:
// - int - row coord of central pixel
int Mask::GetCentralPixelRow() const
{
    return m_centralPixel.y();
}

// Get col coordinate of central pixel
// @output:
// - int - col coord of central pixel
int Mask::GetCentralPixelCol() const
{
    return m_centralPixel.x();
}

// Set coordinates of central pixel
// @input:
// - t_row - row of pixel
// - t_col - column of pixel
void Mask::SetCentralPixel(const int& t_row, const int& t_col)
{
    if ( false == IsPixelExist(t_row, t_col) )
    {
        qDebug() << __FUNCTION__ << "Invalid pixel index";
        return;
    }

    m_centralPixel.setY(t_row);
    m_centralPixel.setX(t_col);
    SetPixelActiveStatus(t_row, t_col, true);
}

// Check if pixel is central
// @input:
// - t_row - row of pixel
// - t_col - column of pixel
// @output:
// - bool - True if pixel is central, False otherwise
bool Mask::IsPixelCentral(const int& t_row, const int& t_col) const
{
    return m_centralPixel.x() == t_col && m_centralPixel.y() == t_row;
}
