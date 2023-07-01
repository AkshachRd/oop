#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>

class CBody
{
public:
	virtual double GetVolume() const = 0;
	virtual double GetDensity() const = 0;
	virtual double GetMass() const = 0;
	std::string ToString() const;

	std::string GetType() const;
	CBody* GetParent() const;
	void SetParent(CBody* parent);
protected:
	CBody(std::string type);
private:
	std::string m_type;
	CBody* m_parent;

	virtual void AppendProperties(std::ostream& strm) const = 0;
};

using BodyPtr = std::shared_ptr<CBody>;