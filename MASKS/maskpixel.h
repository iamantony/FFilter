#ifndef MASK_H
#define MASK_H

class MaskPixel
{
    // == METHODS ==
public:
    explicit MaskPixel();

    void SetEnabled(const bool &t_isEnabled);
    bool IsEnabled() const;
    void SetWieght(const double &t_weight);
    double GetWieght() const;

    // == DATA
private:
    bool m_isEnabled;
    double m_weight;
};

#endif // MASK_H
