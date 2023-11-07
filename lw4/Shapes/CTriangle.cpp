#include "CTriangle.h"
#include "common_libs.h"
#include <iostream>

CTriangle::CTriangle(const CPoint points[3], const uint32_t outlineColor, const uint32_t fillColor)
	: m_points()
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	m_points[0] = points[0];
	m_points[1] = points[1];
	m_points[2] = points[2];
}

double CTriangle::GetArea() const
{
	double p = this->GetPerimeter() / 2;
	CPoint p1 = m_points[0];
	CPoint p2 = m_points[1];
	CPoint p3 = m_points[2];

	double a = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
	double b = sqrt((p3.x - p2.x) * (p3.x - p2.x) + (p3.y - p2.y) * (p3.y - p2.y));
	double c = sqrt((p1.x - p3.x) * (p1.x - p3.x) + (p1.y - p3.y) * (p1.y - p3.y));

	return sqrt(p * (p - a) * (p - b) * (p - c));
}

double CTriangle::GetPerimeter() const
{
	CPoint p1 = m_points[0];
	CPoint p2 = m_points[1];
	CPoint p3 = m_points[2];

	double side1 = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
	double side2 = sqrt((p3.x - p2.x) * (p3.x - p2.x) + (p3.y - p2.y) * (p3.y - p2.y));
	double side3 = sqrt((p1.x - p3.x) * (p1.x - p3.x) + (p1.y - p3.y) * (p1.y - p3.y));

	return side1 + side2 + side3;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CTriangle::GetSpecifiedShapeData() const
{
	std::ostringstream oss;

	oss << "This is a triangle" << std::endl;

	return oss.str();
}