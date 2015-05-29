#ifndef MASKSTRUCTURE_H
#define MASKSTRUCTURE_H

#include <QVector>

#include "masks/maskpixel.h"

class Mask
{
    // == METHODS ==
public:
    explicit Mask(const unsigned int t_rows = 1,
                  const unsigned int t_cols = 1);

    // Does mask have pixels
    bool IsEmpty() const;
    // Set position of central pixel
    bool SetCentralPixel(const unsigned int &t_row, const unsigned int &t_col);
    // Set size of the mask
    bool SetMaskSize(const unsigned int &t_rows, const unsigned int &t_cols);

private:
    // Get index of pixel in pixels container
    int GetPixelIndex(const unsigned int &t_row,
                      const unsigned int &t_col) const;

    // Check if index of pixel is valid
    bool IsIndexValid(const unsigned int &t_index) const;
    bool ResizeMask(const unsigned int &t_rows, const unsigned int &t_cols);


    int GetCentralPixelIndex() const;

    // Check if mask structure is valid
    bool CheckMask();

    // == DATA ==
private:
    unsigned int m_rows;
    unsigned int m_cols;
    unsigned int m_centralPixelRow;
    unsigned int m_centralPixelCol;
    QVector<MaskPixel> m_maskPixels;
};

#endif // MASKSTRUCTURE_H
