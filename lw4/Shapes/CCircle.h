#pragma once
#include "common_libs.h"
#include "CPoint.h"
#include "ISolidShape.h"

class CCircle: public ISolidShape
{
public:
	CCircle(const CPoint& centerPoint, const uint32_t radius, const uint32_t outlineColor = MIN_HEX_COLOR, const uint32_t fillColor = MAX_HEX_COLOR);
	~CCircle() {};
	double GetArea() const final;
	double GetPerimeter() const final;
	uint32_t GetFillColor() const final;
	uint32_t GetOutlineColor() const final;
	std::string GetSpecifiedShapeData() const final;

private:
	CPoint m_centerPoint;
	uint32_t m_radius = 0;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};