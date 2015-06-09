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
    // Set size of the mask
    void SetMaskSize(const unsigned int &t_rows, const unsigned int &t_cols);
    // Get number of rows in mask
    unsigned int GetRowsNum() const;
    // Get number of columns in mask
    unsigned int GetColsNum() const;
    // Check if pixel enabled
    bool IsPixelEnabled(const unsigned int &t_row,
                        const unsigned int &t_col) const;

    // Enable / disable pixel
    void SetPixelActiveStatus(const unsigned int &t_row,
                              const unsigned int &t_col,
                              const bool &t_isEnabled);

    // Get weight of pixel
    double GetPixelWeight(const unsigned int &t_row,
                          const unsigned int &t_col) const;

    // Set wight of pixel
    void SetPixelWeight(const unsigned int &t_row,
                         const unsigned int &t_col,
                         const double &t_weight);

private:
    // Check if pixel woth defined coordinates exist
    bool IsPixelExist(const unsigned int &t_row,
                      const unsigned int &t_col) const;

    // Resize mask
    void ResizeMask(const unsigned int &t_rows, const unsigned int &t_cols);

    // == DATA ==
private:
    QVector< QVector<MaskPixel> > m_maskPixels;
};

#endif // MASKSTRUCTURE_H
