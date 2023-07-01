#pragma once
#include "SolidBody.h"

class CCone : public CSolidBody
{
public:
	CCone(double density, double baseRadius, double height);

	double GetBaseRadius() const;
	double GetHeight() const;
	double GetVolume() const override;
private:
	double m_baseRadius;
	double m_height;

	void AppendProperties(std::ostream& strm) const override;
};