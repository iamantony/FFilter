#ifndef MASK_H
#define MASK_H

class MaskPixel
{
    // == METHODS ==
public:
    explicit MaskPixel();

    void SetEnabled(const bool &t_isEnabled);
    bool IsEnabled() const;
    void SetCentral(const bool &t_isCentral);
    bool IsCentral() const;
    void SetWieght(const double &t_weight);
    double GetWieght() const;

    // == DATA
private:
    bool m_isEnabled;
    bool m_isCentral;
    double m_weight;
};

#endif // MASK_H
