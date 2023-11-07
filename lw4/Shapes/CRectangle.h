#pragma once
#include "common_libs.h"
#include "ISolidShape.h"
#include "CPoint.h"

class CRectangle: public ISolidShape
{
public:
	CRectangle(const CPoint& leftTopPoint, const uint32_t width, const uint32_t height, const uint32_t outlineColor = MIN_HEX_COLOR, const uint32_t fillColor = MAX_HEX_COLOR);
	~CRectangle() {};
	double GetArea() const final;
	double GetPerimeter() const final;
	uint32_t GetFillColor() const final;
	uint32_t GetOutlineColor() const final;
	std::string GetSpecifiedShapeData() const final;

private:
	CPoint m_leftTopPoint;
	uint32_t m_width = 0;
	uint32_t m_height = 0;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};