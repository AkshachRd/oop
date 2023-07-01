#include "Compound.h"

CCompound::CCompound()
	: CBody("compound")
{
};

bool CCompound::AddCompound(const BodyPtr& child)
{
	CBody* addedBody = child.get();
	if (!addedBody || addedBody == this || addedBody->GetParent() != nullptr)
	{
		return false;
	}

	CBody* parent = GetParent();
	while (parent != nullptr)
	{
		if (parent == addedBody)
		{
			return false;
		}
		parent = parent->GetParent();
	}

	addedBody->SetParent(this);
	m_children.push_back(child);
	return true;
};

bool CCompound::AddChildBody(const BodyPtr& child)
{
	if (child->GetType() == "compound")
	{
		return AddCompound(child);
	}
	else
	{
		if (child->GetParent() == nullptr)
		{
			child->SetParent(this);
			m_children.push_back(child);
			return true;
		}
	}

	return false;
};

double CCompound::GetMass() const
{
	double mass = 0;

	for (auto& body : m_children)
	{
		mass += body->GetMass();
	}

	return mass;
};

double CCompound::GetVolume() const
{
	double volume = 0;

	for (auto& body : m_children)
	{
		volume += body->GetVolume();
	}

	return volume;
};

double CCompound::GetDensity() const
{
	double volume = GetVolume();
	if (volume != 0)
	{
		return GetMass() / volume;
	}
	else
	{
		return 0;
	}
};

void CCompound::AppendProperties(std::ostream& strm) const
{
	strm << std::endl << "{" << std::endl;
	for (auto& child : m_children)
	{
		strm << child->ToString() << std::endl;
	}
	strm << "}";
}