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

    // Set size of the mask
    bool SetMaskSize(const unsigned int &t_rows, const unsigned int &t_cols);
    bool IsEmpty() const;

private:
    bool ResizeMask(const unsigned int &t_rows, const unsigned int &t_cols);
    int GetPixelIndex(const unsigned int &t_row,
                      const unsigned int &t_col) const;
    int GetCentralPixelIndex() const;

    // Check if mask structure is valid
    bool CheckMask();

    // == DATA ==
private:
    unsigned int m_rows;
    unsigned int m_cols;
    QVector<MaskPixel> m_maskPixels;
};

#endif // MASKSTRUCTURE_H
