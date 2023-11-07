#pragma once
#include "common_libs.h"
#include "IShape.h"

class ISolidShape: public IShape
{
public:
	virtual ~ISolidShape() {};
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual uint32_t GetFillColor() const = 0;
};