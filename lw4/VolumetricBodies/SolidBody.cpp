#include "SolidBody.h"

CSolidBody::CSolidBody(std::string type, double density)
	: CBody(type),
	m_density(density)
{
};

double CSolidBody::GetDensity() const
{
	return m_density;
};

double CSolidBody::GetMass() const
{
	return m_density * GetVolume();
};