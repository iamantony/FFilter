#ifndef MASKSTRUCTURE_H
#define MASKSTRUCTURE_H

#include <QVector>
#include <QPoint>

#include "masks/maskpixel.h"

class Mask
{
    // == METHODS ==
public:
    explicit Mask(const int t_rows = 1,
                  const int t_cols = 1);

    // Does mask have pixels
    bool IsEmpty() const;
    // Set size of the mask
    void SetMaskSize(const int& t_rows, const int& t_cols);
    // Get number of rows in mask
    int GetRowsNum() const;
    // Get number of columns in mask
    int GetColsNum() const;
    // Check if pixel enabled
    bool IsPixelEnabled(const int& t_row, const int& t_col) const;
    // Enable / disable pixel
    void SetPixelActiveStatus(const int& t_row,
                              const int& t_col,
                              const bool& t_isEnabled);

    // Get weight of pixel
    double GetPixelWeight(const int& t_row, const int& t_col) const;

    // Set wight of pixel
    void SetPixelWeight(const int& t_row,
                        const int& t_col,
                        const double& t_weight);

    // Get row coordinate of central pixel
    int GetCentralPixelRow() const;
    // Get col coordinate of central pixel
    int GetCentralPixelCol() const;
    // Set coordinates of central pixel
    void SetCentralPixel(const int& t_row, const int& t_col);
    // Check if pixel is central
    bool IsPixelCentral(const int& t_row, const int& t_col) const;

private:
    // Check if pixel woth defined coordinates exist
    bool IsPixelExist(const int& t_row,
                      const int& t_col) const;

    // Resize mask
    void ResizeMask(const int& t_rows, const int& t_cols);

    // == DATA ==
private:
    QPoint m_centralPixel;
    QVector< QVector<MaskPixel> > m_maskPixels;
};

#endif // MASKSTRUCTURE_H
