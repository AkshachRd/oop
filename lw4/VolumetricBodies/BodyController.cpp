#include "BodyController.h"

using namespace std::placeholders;

CBodyController::CBodyController(std::vector<BodyPtr>& bodies, std::istream& input, std::ostream& output)
	:m_bodies(bodies),
	m_input(input),
	m_output(output),
	m_actionMap({
		{"sphere", std::bind(&CBodyController::CreateSphere, this, _1)},
		{"parallelepiped", std::bind(&CBodyController::CreateParallelepiped, this, _1)},
		{"cone", std::bind(&CBodyController::CreateCone, this, _1)},
		{"cylinder", std::bind(&CBodyController::CreateCylinder, this, _1)}
	})
{
};

bool CBodyController::CreateBodies()
{
	std::string str;
	getline(m_input, str);
	if (m_input.eof())
	{
		return true;
	}
	std::stringstream strm(str);

	std::string actionBody;
	strm >> actionBody;


	auto it = m_actionMap.find(actionBody);
	if (it != m_actionMap.end())
	{
		auto bodyPtr = it->second(strm);
		if (bodyPtr)
		{
			m_bodies.push_back(bodyPtr);
		}
		return true;
	}
	else if (actionBody == "compound")
	{

		auto compoundPtr = CreateCompound();
		if (compoundPtr)
		{
			m_bodies.push_back(compoundPtr);
		}

		return true;
	}
	else
	{
		return false;
	}
};

BodyPtr CBodyController::CreateSphere(std::istream& args)
{
	double density;
	double radius;

	if (ReadNum(args, density) && ReadNum(args, radius))
	{
		m_output << "The sphere has been successfully created" << std::endl;
		return std::make_shared<CSphere>(density, radius);
	}
	else
	{
		m_output << "Sphere data not entered correctly" << std::endl;
		return nullptr;
	}
};

BodyPtr CBodyController::CreateParallelepiped(std::istream& args)
{
	double density;
	double height;
	double width;
	double depth;

	if (ReadNum(args, density) && ReadNum(args, height) && ReadNum(args, width) && ReadNum(args, depth))
	{
		m_output << "The parallelepiped has been successfully created" << std::endl;
		return std::make_shared<CParallelepiped>(density, height, width, depth);
	}
	else
	{
		m_output << "Parallelepiped data not entered correctly" << std::endl;
		return nullptr;
	}
};

BodyPtr CBodyController::CreateCone(std::istream& args)
{
	double density;
	double baseRadius;
	double height;

	if (ReadNum(args, density) && ReadNum(args, baseRadius) && ReadNum(args, height))
	{
		m_output << "The cone has been successfully created" << std::endl;
		return std::make_shared<CCone>(density, baseRadius, height);
	}
	else
	{
		m_output << "Cone data not entered correctly" << std::endl;
		return nullptr;
	}
};

BodyPtr CBodyController::CreateCylinder(std::istream& args)
{
	double density;
	double baseRadius;
	double height;

	if (ReadNum(args, density) && ReadNum(args, baseRadius) && ReadNum(args, height))
	{
		m_output << "The cylinder has been successfully created" << std::endl;
		return std::make_shared<CCylinder>(density, baseRadius, height);
	}
	else
	{
		m_output << "Cylinder data not entered correctly" << std::endl;
		return nullptr;
	}
};

BodyPtr CBodyController::CreateCompound()
{
	std::shared_ptr<CCompound> compoundBody(new CCompound());

	std::string bodyInfo;
	
	while (getline(m_input, bodyInfo) && bodyInfo.length() != 0)
	{
		std::stringstream bodyArgs(bodyInfo);

		std::string bodyType;
		bodyArgs >> bodyType;

		auto it = m_actionMap.find(bodyType);
		if (it != m_actionMap.end())
		{
			auto bodyPtr = it->second(bodyArgs);
			if (bodyPtr)
			{
				compoundBody->AddChildBody(bodyPtr);
			}
		}
		else if (bodyType == "compound")
		{
			auto compoundPtr = CreateCompound();
			if (compoundPtr)
			{
				compoundBody->AddChildBody(compoundPtr);
			}
		}
	}

	m_output << "The compound body has been successfully created" << std::endl;
	return compoundBody;
};

bool CBodyController::ReadNum(std::istream& args, double& num)
{
	std::string arg;
	args >> arg;
	try
	{
		num = std::stod(arg);
		return true;
	}
	catch (const std::invalid_argument& e)
	{
		return false;
	}
};