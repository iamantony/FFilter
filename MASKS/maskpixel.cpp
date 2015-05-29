#include "masks/maskpixel.h"

MaskPixel::MaskPixel() : m_isEnabled(false), m_isCentral(false), m_weight(0.0)
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

void MaskPixel::SetCentral(const bool &t_isCentral)
{
    m_isCentral = t_isCentral;
}

bool MaskPixel::IsCentral() const
{
    return m_isCentral;
}

void MaskPixel::SetWieght(const double &t_weight)
{
    m_weight = t_weight;
}

double MaskPixel::GetWieght() const
{
    return m_weight;
}
