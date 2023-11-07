#pragma once
#include "common_libs.h"

class CPoint
{
public:
	CPoint(const uint32_t x, const uint32_t y);
	CPoint();
	~CPoint() {};

	bool operator==(const CPoint& comparable) const;

	uint32_t x = 0;
	uint32_t y = 0;
};