#pragma once
#include "Body.h"

class CSolidBody : public CBody
{
public:
	CSolidBody(std::string type, double density);

	double GetMass() const override;
	double GetDensity() const override;
private:
	double m_density;
};