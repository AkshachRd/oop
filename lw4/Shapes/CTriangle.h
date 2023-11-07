#pragma once
#include "common_libs.h"
#include "ISolidShape.h"
#include "CPoint.h"

class CTriangle: public ISolidShape
{
public:
	CTriangle(const CPoint points[3], const uint32_t outlineColor = MIN_HEX_COLOR, const uint32_t fillColor = MAX_HEX_COLOR);
	~CTriangle() {};
	double GetArea() const final;
	double GetPerimeter() const final;
	uint32_t GetFillColor() const final;
	uint32_t GetOutlineColor() const final;
	std::string GetSpecifiedShapeData() const final;

private:
	CPoint m_points[3];
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};