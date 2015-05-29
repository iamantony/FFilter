#include "masks/maskpixel.h"

MaskPixel::MaskPixel() : m_isEnabled(false), m_weight(0.0)
{
}

void MaskPixel::SetEnabled(const bool &t_isEnabled)
{
    m_isEnabled = t_isEnabled;
}

bool MaskPixel::IsEnabled() const
{
    return m_isEnabled;
}

void MaskPixel::SetWieght(const double &t_weight)
{
    m_weight = t_weight;
}

double MaskPixel::GetWieght() const
{
    return m_weight;
}
