#include "CController.h"
#include "CLine.h"
#include "CCircle.h"
#include "CTriangle.h"
#include "ISolidShape.h"
#include "CRectangle.h"

CController::CController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "line", bind(&CController::HandleLine, this, std::placeholders::_1) },
		  { "circle", bind(&CController::HandleCircle, this, std::placeholders::_1) },
		  { "triangle", bind(&CController::HandleTriangle, this, std::placeholders::_1) },
		  { "rectangle", bind(&CController::HandleRectangle, this, std::placeholders::_1) },
		  { "help", bind(&CController::Help, this, std::placeholders::_1) }
		})
{
}

bool CController::HandleCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		try
		{
			return it->second(strm);
		}
		catch (std::exception const& e)
		{
			throw;
		}
	}

	return false;
}

bool CController::GetShapesInfo()
{
	auto maxAreaShapeIt = std::min_element(m_solidShapes.begin(), m_solidShapes.end(),
		[&](const std::unique_ptr<ISolidShape>& firstShape, const std::unique_ptr<ISolidShape>& secondShape) {
			return firstShape->GetArea() > secondShape->GetArea();
		});
	auto minPerimeterShapeIt = std::min_element(m_solidShapes.begin(), m_solidShapes.end(),
		[&](const std::unique_ptr<ISolidShape>& firstShape, const std::unique_ptr<ISolidShape>& secondShape) {
			return firstShape->GetPerimeter() < secondShape->GetPerimeter();
		});

	if (maxAreaShapeIt != m_solidShapes.end()) {
		m_output << "Max area shape:" << std::endl
		<< "Area: " << (*maxAreaShapeIt)->GetArea() << std::endl
	    << "Perimeter: " << (*maxAreaShapeIt)->GetPerimeter() << std::endl
		<< "Outline color: " << std::hex << (*maxAreaShapeIt)->GetOutlineColor() << std::endl
		<< "Fill color: " << (*maxAreaShapeIt)->GetFillColor() << std::endl
		<< "Specific data: " << (*maxAreaShapeIt)->GetSpecifiedShapeData() << std::endl;
	}
	if (minPerimeterShapeIt != m_solidShapes.end()) {
		m_output << "Min perimeter shape:" << std::endl
		<< "Area: " << (*minPerimeterShapeIt)->GetArea() << std::endl
		<< "Perimeter: " << (*minPerimeterShapeIt)->GetPerimeter() << std::endl
    	<< "Outline color: " << (*minPerimeterShapeIt)->GetOutlineColor() << std::endl
		<< "Fill color: " << (*minPerimeterShapeIt)->GetFillColor() << std::endl
		<< "Specific data: " << (*minPerimeterShapeIt)->GetSpecifiedShapeData() << std::endl;
	}

	return true;
}

bool CController::HandleLine(std::istream& args)
{
	try
	{
		CController::LineArgs parsedArgs = ParseLineArgs(args);

		CLine line = CLine(parsedArgs.fromPoint, parsedArgs.toPoint, parsedArgs.outlineColor);
		m_shapes.push_back(std::make_unique<CLine>(line));
	}
	catch (std::exception const& e)
	{
		throw;
	}

	return true;
}

bool CController::HandleCircle(std::istream& args)
{
	CController::CircleArgs parsedArgs = ParseCircleArgs(args);

	CCircle circle = CCircle(parsedArgs.centerPoint, parsedArgs.radius, parsedArgs.outlineColor, parsedArgs.fillColor);
	m_shapes.push_back(std::make_unique<CCircle>(circle));
	m_solidShapes.push_back(std::make_unique<CCircle>(circle));

	return true;
}

bool CController::HandleTriangle(std::istream& args)
{
	CController::TriangleArgs parsedArgs = ParseTriangleArgs(args);

	CTriangle triangle = CTriangle(parsedArgs.points, parsedArgs.outlineColor, parsedArgs.fillColor);
	m_shapes.push_back(std::make_unique<CTriangle>(triangle));
	m_solidShapes.push_back(std::make_unique<CTriangle>(triangle));

	return true;
}

bool CController::HandleRectangle(std::istream& args)
{
	CController::RectangleArgs parsedArgs = ParseRectangleArgs(args);

	CRectangle rectangle = CRectangle(parsedArgs.leftTopPoint, parsedArgs.width, parsedArgs.height,
		parsedArgs.outlineColor, parsedArgs.fillColor);
	m_shapes.push_back(std::make_unique<CRectangle>(rectangle));
	m_solidShapes.push_back(std::make_unique<CRectangle>(rectangle));

	return true;
}

bool CController::Help(std::istream&)
{
	m_output << "Available commands:" << std::endl
		<< "line <from x> <from y> <to x> <to y> <outlineColor(hex)>" << std::endl
		<< "circle <center x> <center y> <radius> <outlineColor(hex)> <fillColor(hex)>" << std::endl
		<< "rectangle <left top x> <left top y> <width> <height> <outlineColor(hex)> <fillColor(hex)>" << std::endl
		<< "triangle <first x> <first y> <second x> <second y> <third x> <third y> <outlineColor(hex)> <fillColor(hex)>" << std::endl;

	return true;
}

CController::LineArgs CController::ParseLineArgs(std::istream& args)
{
	std::string argsString;
	std::getline(args, argsString);
	const std::vector<std::string> splittedArgs = split(argsString, ' ');
	if (splittedArgs.size() != 6)
	{
		m_output << "Incorrect args count" << std::endl;
	}
	const std::string fromXString = splittedArgs[1];
	const std::string fromYString = splittedArgs[2];
	const std::string toXString = splittedArgs[3];
	const std::string toYString = splittedArgs[4];
	const std::string outlineColorString = splittedArgs[5];

	if (fromXString[0] == '-')
	{
		throw std::invalid_argument("<from x> is negative. Point's coordinate can not be negative");
	}
	uint32_t fromX = 0;
	try
	{
		fromX = static_cast<uint32_t>(std::stoul(fromXString));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <from x> to unsigned number");
	}

	if (fromYString[0] == '-')
	{
		throw std::invalid_argument("<from y> is negative. Point's coordinate can not be negative");
	}
	uint32_t fromY = 0;
	try
	{
		fromY = static_cast<uint32_t>(std::stoul(fromYString));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <from y> to unsigned number");
	}

	if (toXString[0] == '-')
	{
		throw std::invalid_argument("<to x> is negative. Point's coordinate can not be negative");
	}
	uint32_t toX = 0;
	try
	{
		toX = static_cast<uint32_t>(std::stoul(toXString));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <to x> to unsigned number");
	}

	if (toYString[0] == '-')
	{
		throw std::invalid_argument("<to y> is negative. Point's coordinate can not be negative");
	}
	uint32_t toY = 0;
	try
	{
		toY = static_cast<uint32_t>(std::stoul(toYString));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <to y> to unsigned number");
	}

	if (outlineColorString[0] == '-')
	{
		throw std::invalid_argument("<outline color> is negative. Outline color can not be negative");
	}
	uint32_t outlineColor = MIN_HEX_COLOR;
	try
	{
		outlineColor = static_cast<uint32_t>(std::stoul("0x" + outlineColorString, nullptr, 16));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <outline color> to hex");
	}
	if (outlineColor < 0 || outlineColor > MAX_HEX_COLOR)
	{
		throw std::invalid_argument("<outline color> can be in 0 .. ffffff");
	}

	const CPoint fromPoint = CPoint(fromX, fromY);
	const CPoint toPoint = CPoint(toX, toY);

	return { fromPoint, toPoint, outlineColor};
}

CController::RectangleArgs CController::ParseRectangleArgs(std::istream& args)
{
	std::string argsString;
	std::getline(args, argsString);
	const std::vector<std::string> splittedArgs = split(argsString, ' ');
	if (splittedArgs.size() != 7)
	{
		m_output << "Incorrect args count" << std::endl;
	}
	const std::string leftTopXString = splittedArgs[1];
	const std::string leftTopYString = splittedArgs[2];
	const std::string widthString = splittedArgs[3];
	const std::string heightString = splittedArgs[4];
	const std::string outlineColorString = splittedArgs[5];
	const std::string fillColorString = splittedArgs[6];

	if (leftTopXString[0] == '-')
	{
		throw std::invalid_argument("<left top x> is negative. Point's coordinate can not be negative");
	}
	uint32_t leftTopX = 0;
	try
	{
		leftTopX = static_cast<uint32_t>(std::stoul(leftTopXString));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <left top x> to unsigned number");
	}

	if (leftTopYString[0] == '-')
	{
		throw std::invalid_argument("<left top y> is negative. Point's coordinate can not be negative");
	}
	uint32_t leftTopY = 0;
	try
	{
		leftTopY = static_cast<uint32_t>(std::stoul(leftTopYString));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <left top y> to unsigned number");
	}

	if (widthString[0] == '-')
	{
		throw std::invalid_argument("<width> is negative. Point's coordinate can not be negative");
	}
	uint32_t width = 0;
	try
	{
		width = static_cast<uint32_t>(std::stoul(widthString));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <width> to unsigned number");
	}

	if (heightString[0] == '-')
	{
		throw std::invalid_argument("<height> is negative. Point's coordinate can not be negative");
	}
	uint32_t height = 0;
	try
	{
		height = static_cast<uint32_t>(std::stoul(heightString));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <height> to unsigned number");
	}

	if (outlineColorString[0] == '-')
	{
		throw std::invalid_argument("<outline color> is negative. Outline color can not be negative");
	}
	uint32_t outlineColor = MIN_HEX_COLOR;
	try
	{
		outlineColor = static_cast<uint32_t>(std::stoul("0x" + outlineColorString, nullptr, 16));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <outline color> to hex");
	}
	if (outlineColor < 0 || outlineColor > MAX_HEX_COLOR)
	{
		throw std::invalid_argument("<outline color> can be in 0 .. ffffff");
	}

	if (fillColorString[0] == '-')
	{
		throw std::invalid_argument("<fill color> is negative. Fill color can not be negative");
	}
	uint32_t fillColor = 0;
	try
	{
		fillColor = static_cast<uint32_t>(std::stoul("0x" + fillColorString, nullptr, 16));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <fill color> to hex");
	}
	if (fillColor < 0 || fillColor > MAX_HEX_COLOR)
	{
		throw std::invalid_argument("<fill color> can be in 0 .. ffffff");
	}

	CPoint leftTopPoint = CPoint(leftTopX, leftTopY);

	return { leftTopPoint, width, height, outlineColor, fillColor };
}

CController::CircleArgs CController::ParseCircleArgs(std::istream& args)
{
	std::string argsString;
	std::getline(args, argsString);
	const std::vector<std::string> splittedArgs = split(argsString, ' ');
	if (splittedArgs.size() != 6)
	{
		m_output << "Incorrect args count" << std::endl;
	}

	const std::string centerXString = splittedArgs[1];
	const std::string centerYString = splittedArgs[2];
	const std::string radiusString = splittedArgs[3];
	const std::string outlineColorString = splittedArgs[4];
	const std::string fillColorString = splittedArgs[5];

	if (centerXString[0] == '-')
	{
		throw std::invalid_argument("<center x> is negative. Point's coordinate can not be negative");
	}
	uint32_t centerX = 0;
	try
	{
		centerX = static_cast<uint32_t>(std::stoul(centerXString));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <center x> to unsigned number");
	}

	if (centerYString[0] == '-')
	{
		throw std::invalid_argument("<center y> is negative. Point's coordinate can not be negative");
	}
	uint32_t centerY = 0;
	try
	{
		centerY = static_cast<uint32_t>(std::stoul(centerYString));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <center y> to unsigned number");
	}

	if (radiusString[0] == '-')
	{
		throw std::invalid_argument("<radius> is negative. Point's coordinate can not be negative");
	}
	uint32_t radius = 0;
	try
	{
		radius = static_cast<uint32_t>(std::stoul(radiusString));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <radius> to unsigned number");
	}

	if (outlineColorString[0] == '-')
	{
		throw std::invalid_argument("<outline color> is negative. Outline color can not be negative");
	}
	uint32_t outlineColor = MIN_HEX_COLOR;
	try
	{
		outlineColor = static_cast<uint32_t>(std::stoul("0x" + outlineColorString, nullptr, 16));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <outline color> to hex");
	}
	if (outlineColor < 0 || outlineColor > MAX_HEX_COLOR)
	{
		throw std::invalid_argument("<outline color> can be in 0 .. ffffff");
	}

	if (fillColorString[0] == '-')
	{
		throw std::invalid_argument("<fill color> is negative. Fill color can not be negative");
	}
	uint32_t fillColor = 0;
	try
	{
		fillColor = static_cast<uint32_t>(std::stoul("0x" + fillColorString, nullptr, 16));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <fill color> to hex");
	}
	if (fillColor < 0 || fillColor > MAX_HEX_COLOR)
	{
		throw std::invalid_argument("<fill color> can be in 0 .. ffffff");
	}

	CPoint centerPoint = CPoint(centerX, centerY);

	return { centerPoint, radius, outlineColor, fillColor };
}

CController::TriangleArgs CController::ParseTriangleArgs(std::istream& args)
{
	std::string argsString;
	std::getline(args, argsString);
	const std::vector<std::string> splittedArgs = split(argsString, ' ');
	if (splittedArgs.size() != 9)
	{
		m_output << "Incorrect args count" << std::endl;
	}

	CPoint points[3];
	uint32_t currIndex = 1;
	std::string arg = std::string();
	for(int currIndex = 1; currIndex < 7; currIndex++)
	{
		arg = splittedArgs[currIndex];
		if (currIndex % 2 != 0)
		{
			try
			{
				uint32_t pointX = static_cast<uint32_t>(std::stoul(arg));
				points[(currIndex - 1) / 2] = CPoint(pointX, 0);
			}
			catch (std::exception const& e)
			{
				throw std::invalid_argument("Can not convert <point x> to unsigned number");
			}
		}
		else
		{
			try
			{
				uint32_t pointY = static_cast<uint32_t>(std::stoul(arg));
				points[(currIndex - 1) / 2].y = pointY;
			}
			catch (std::exception const& e)
			{
				throw std::invalid_argument("Can not convert <point y> to unsigned number");
			}
		}
	}

	const std::string outlineColorString = splittedArgs[splittedArgs.size() - 2];
	const std::string fillColorString = splittedArgs[splittedArgs.size() - 1];

	if (outlineColorString[0] == '-')
	{
		throw std::invalid_argument("<outline color> is negative. Outline color can not be negative");
	}
	uint32_t outlineColor = MIN_HEX_COLOR;
	try
	{
		outlineColor = static_cast<uint32_t>(std::stoul("0x" + outlineColorString, nullptr, 16));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <outline color> to hex");
	}
	if (outlineColor < 0 || outlineColor > MAX_HEX_COLOR)
	{
		throw std::invalid_argument("<outline color> can be in 0 .. ffffff");
	}

	if (fillColorString[0] == '-')
	{
		throw std::invalid_argument("<fill color> is negative. Fill color can not be negative");
	}
	uint32_t fillColor = 0;
	try
	{
		fillColor = static_cast<uint32_t>(std::stoul("0x" + fillColorString, nullptr, 16));
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument("Can not convert <fill color> to hex");
	}
	if (fillColor < 0 || fillColor > MAX_HEX_COLOR)
	{
		throw std::invalid_argument("<fill color> can be in 0 .. ffffff");
	}

	return { {points[0], points[1], points[2]}, outlineColor, fillColor };
}