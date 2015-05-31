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
        m_maskPixels.clear();
        m_centralPixelRow = 0;
        m_centralPixelCol = 0;

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
