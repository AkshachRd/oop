#pragma once
#include "Body.h"
#include <vector>

class CCompound : public CBody
{
public:
	CCompound();

	double GetMass() const override;
	double GetVolume() const override;
	double GetDensity() const override;

	bool AddChildBody(const BodyPtr& child);
	bool AddCompound(const BodyPtr& body);
private:
	std::vector<BodyPtr> m_children;

	void AppendProperties(std::ostream& strm) const override;
};