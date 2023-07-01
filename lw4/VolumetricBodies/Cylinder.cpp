#include "Cylinder.h"
#define _USE_MATH_DEFINES
#include <math.h>

CCylinder::CCylinder(double density, double baseRadius, double height)
	: CSolidBody("cylinder", density),
	m_baseRadius(baseRadius),
	m_height(height)
{
};

double CCylinder::GetBaseRadius() const
{
	return m_baseRadius;
};

double CCylinder::GetHeight() const
{
	return m_height;
};

double CCylinder::GetVolume() const
{
	return pow(m_baseRadius, 2) * M_PI * m_height;
};

void CCylinder::AppendProperties(std::ostream& strm) const
{
	strm << "Base radius: " << round(GetBaseRadius() * 1000) / 1000 << ". "
		<< "Height: " << round(GetHeight() * 1000) / 1000 << ".";
};