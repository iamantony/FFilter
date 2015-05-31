#ifndef MASKSTRUCTURE_H
#define MASKSTRUCTURE_H

#include <QVector>

#include "masks/maskpixel.h"

class Mask
{
    // == METHODS ==
public:
    explicit Mask(const unsigned int t_rows = 0,
                  const unsigned int t_cols = 0);

    // Does mask have pixels
    bool IsEmpty() const;
    // Set position of central pixel
    bool SetCentralPixel(const unsigned int &t_row, const unsigned int &t_col);
    // Set size of the mask
    void SetMaskSize(const unsigned int &t_rows, const unsigned int &t_cols);

private:
    // Check if pixel woth defined coordinates exist
    bool IsPixelExist(const unsigned int &t_row,
                      const unsigned int &t_col) const;

    // Resize mask
    void ResizeMask(const unsigned int &t_rows, const unsigned int &t_cols);

    // == DATA ==
private:
    unsigned int m_centralPixelRow;
    unsigned int m_centralPixelCol;
    QVector< QVector<MaskPixel> > m_maskPixels;
};

#endif // MASKSTRUCTURE_H
