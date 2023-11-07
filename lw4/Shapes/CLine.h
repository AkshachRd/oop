#pragma once
#include "common_libs.h"
#include "IShape.h"
#include "CPoint.h"

class CLine: public IShape
{
public:
	CLine(const CPoint& from, const CPoint& to, const uint32_t outlineColor = MIN_HEX_COLOR);
	~CLine(){};
	uint32_t GetOutlineColor() const override final;
	std::string GetSpecifiedShapeData() const override final;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	uint32_t m_outlineColor;
};