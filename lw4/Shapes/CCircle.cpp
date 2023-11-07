#include "CCircle.h"
#include "common_libs.h"

CCircle::CCircle(const CPoint& centerPoint, const uint32_t radius, const uint32_t outlineColor, const uint32_t fillColor)
	: m_centerPoint(centerPoint)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CCircle::GetSpecifiedShapeData() const
{
	std::ostringstream oss;

	oss << "This is a circle" << std::endl;

	return oss.str();
}