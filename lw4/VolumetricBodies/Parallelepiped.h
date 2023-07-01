#pragma once
#include "SolidBody.h"

class CParallelepiped : public CSolidBody
{
public:
	CParallelepiped(double density, double height, double width, double depth);

	double GetWidth() const;
	double GetHeight() const;
	double GetDepth() const;
	double GetVolume() const override;
private:
	double m_height;
	double m_width;
	double m_depth;

	void AppendProperties(std::ostream& strm) const override;
};