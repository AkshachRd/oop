#pragma once
#include "Sphere.h"
#include "Parallelepiped.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Compound.h"
#include <map>
#include <functional>
#include <string>
#include <sstream>

class CBodyController
{
public:
	CBodyController(std::vector<BodyPtr>& bodies, std::istream& input, std::ostream& output);

	bool CreateBodies();
private:
	BodyPtr CreateSphere(std::istream& args);
	BodyPtr CreateParallelepiped(std::istream& args);
	BodyPtr CreateCone(std::istream& args);
	BodyPtr CreateCylinder(std::istream& args);
	BodyPtr CreateCompound();

	std::vector<BodyPtr>& m_bodies;
	std::istream& m_input;
	std::ostream& m_output;

	using ActionMap = std::map<std::string, std::function<BodyPtr(std::istream& args)>>;

	ActionMap m_actionMap;

	bool ReadNum(std::istream& args, double& num);
};