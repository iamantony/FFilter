#include "masks/mask.h"

#include <QDebug>

Mask::Mask(const unsigned int t_rows, const unsigned int t_cols)
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

// Set position of central pixel
// @input:
// - t_row - row of central pixel
// - t_col - column of central pixel
// @output:
// - bool - True if central pixel set, False otherwise
bool Mask::SetCentralPixel(const unsigned int &t_row, const unsigned int &t_col)
{
    if ( IsPixelExist( t_row, t_col ) )
    {
        m_centralPixelRow = t_row;
        m_centralPixelCol = t_col;

        return true;
    }

    return false;
}

// Check if pixel woth defined coordinates exist
// @input:
// - t_row - row of pixel
// - t_col - column of pixel
// @output:
// - bool - True if pixel exist, False otherwise
bool Mask::IsPixelExist(const unsigned int &t_row,
                        const unsigned int &t_col) const
{
    if ( t_row < static_cast<unsigned int>(m_maskPixels.size()) &&
         t_col < static_cast<unsigned int>(m_maskPixels.first().size()) )
    {
        return true;
    }

    return false;
}

// Set size of the mask
// @input:
// - t_rows - new number of rows
// - t_cols - new number of columns
void Mask::SetMaskSize(const unsigned int &t_rows, const unsigned int &t_cols)
{
    ResizeMask(t_rows, t_cols);
}

// Resize mask
// @input:
// - t_rows - new number of rows
// - t_cols - new number of columns
void Mask::ResizeMask(const unsigned int &t_rows, const unsigned int &t_cols)
{
    if ( 0 == t_rows || 0 == t_cols )
    {
        qDebug() << __func__ << "Invalid mask size";
        return;
    }

    if ( t_rows == static_cast<unsigned int>(m_maskPixels.size()) &&
         t_cols == static_cast<unsigned int>(m_maskPixels.first().size()) )
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
        SetCentralPixel(0, 0);
    }
    else
    {
        m_centralPixelRow = qMin<unsigned int>(m_centralPixelRow,
                                               m_maskPixels.size());

        m_centralPixelCol = qMin<unsigned int>(m_centralPixelCol,
                                 m_maskPixels.first().size());
    }
}

// Get number of rows in mask
// @output:
// - unsigned int - number of rows in mask
unsigned int Mask::GetRowsNum() const
{
    return m_maskPixels.size();
}

// Get number of columns in mask
// @output:
// - unsigned int - number of columns in mask
unsigned int Mask::GetColsNum() const
{
    return m_maskPixels.first().size();
}

// Get row of central pixel
// @output:
// - unsigned int - number of row of central pixel
unsigned int Mask::GetCentralPixelRow() const
{
    return m_centralPixelRow;
}

// Get columns of central pixel
// @output:
// - unsigned int - number of columns of central pixel
unsigned int Mask::GetCentralPixelCol() const
{
    return m_centralPixelCol;
}

// Check if pixel enabled
// @input:
// - t_row - row of pixel
// - t_col - column of pixel
// @output:
// - bool - True if pixel enabled, False otherwise
bool Mask::IsPixelEnabled(const unsigned int &t_row,
                          const unsigned int &t_col) const
{
    if ( false == IsPixelExist(t_row, t_col) )
    {
        qDebug() << __func__ << "Invalid pixel index";
        return false;
    }

    return m_maskPixels.at(t_row).at(t_col).IsEnabled();
}

// Enable / disable pixel
// @input:
// - t_row - row of pixel
// - t_col - column of pixel
// - t_isEnabled - pixel status
void Mask::SetPixelActiveStatus(const unsigned int &t_row,
                                const unsigned int &t_col,
                                const bool &t_isEnabled)
{
    if ( false == IsPixelExist(t_row, t_col) )
    {
        qDebug() << __func__ << "Invalid pixel index";
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
double Mask::GetPixelWeight(const unsigned int &t_row,
                             const unsigned int &t_col) const
{
    if ( false == IsPixelExist(t_row, t_col) )
    {
        qDebug() << __func__ << "Invalid pixel index";
        return 0.0;
    }

    return m_maskPixels.at(t_row).at(t_col).GetWieght();
}

// Set weight of pixel
// @input:
// - t_row - row of pixel
// - t_col - column of pixel
// - t_weight - new weight of pixel
void Mask::SetPixelWeight(const unsigned int &t_row,
                          const unsigned int &t_col,
                          const double &t_weight)
{
    if ( false == IsPixelExist(t_row, t_col) )
    {
        qDebug() << __func__ << "Invalid pixel index";
        return;
    }

    m_maskPixels[t_row][t_col].SetWieght(t_weight);
}
