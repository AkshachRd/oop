#include "CLine.h"
#include "common_libs.h"

CLine::CLine(const CPoint& from, const CPoint& to, const uint32_t outlineColor)
	: m_startPoint(from)
	, m_endPoint(to)
	, m_outlineColor(outlineColor)
{
}

uint32_t CLine::GetOutlineColor() const
{
	return CLine::m_outlineColor;
}

std::string CLine::GetSpecifiedShapeData() const
{
	std::ostringstream oss;

	oss << "This is a line" << std::endl;

	return oss.str();
}