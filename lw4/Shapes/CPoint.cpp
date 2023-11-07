#include "CPoint.h"
#include "common_libs.h"

CPoint::CPoint(const uint32_t x, const uint32_t y)
	: x(x)
	, y(y)
{
}

CPoint::CPoint()
	: x(0)
	, y(0)
{
}

bool CPoint::operator==(const CPoint& comparable) const
{
	return (this->x == comparable.x) && (this->y == comparable.y);
}