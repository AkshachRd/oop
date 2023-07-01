#include "Body.h"

CBody::CBody(std::string type)
	:m_type(type),
	m_parent(nullptr)
{
};

CBody* CBody::GetParent() const
{
	return m_parent;
};

void CBody::SetParent(CBody* parent)
{
	m_parent = parent;
}

std::string CBody::GetType() const
{
	return m_type;
};

std::string CBody::ToString() const
{
	std::ostringstream info;
	info << "Body type: " << m_type << ". "
		<< "Mass: " << round(GetMass() * 1000) / 1000 << ". "
		<< "Volume: " << round(GetVolume() * 1000) / 1000 << ". "
		<< "Density: " << round(GetDensity() * 1000) / 1000 << ". ";

	AppendProperties(info);

	return info.str();
};