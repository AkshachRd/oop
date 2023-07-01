#include "Cone.h"
#define _USE_MATH_DEFINES
#include <math.h>

CCone::CCone(double density, double baseRadius, double height)
	: CSolidBody("cone", density),
	m_baseRadius(baseRadius),
	m_height(height)
{
};

double CCone::GetBaseRadius() const
{
	return m_baseRadius;
};

double CCone::GetHeight() const
{
	return m_height;
};

double CCone::GetVolume() const
{
	return pow(m_baseRadius, 2) * m_height * M_PI / 3;
};

void CCone::AppendProperties(std::ostream& strm) const
{
	strm << "Base radius: " << round(GetBaseRadius() * 1000) / 1000 << ". "
		<< "Height: " << round(GetHeight() * 1000) / 1000 << ".";
};