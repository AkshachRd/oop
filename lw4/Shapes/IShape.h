#pragma once
#include "common_libs.h"

class IShape
{
public:
	virtual ~IShape() {};
	virtual uint32_t GetOutlineColor() const = 0;
	virtual std::string GetSpecifiedShapeData() const = 0;
};