#pragma once
#include "common_libs.h"
#include "ISolidShape.h"
#include "CPoint.h"

class CController
{
public:
	class CController(std::istream& input, std::ostream& output);
	bool HandleCommand();
	bool GetShapesInfo();

private:
	bool HandleLine(std::istream& args);
	bool HandleCircle(std::istream& args);
	bool HandleTriangle(std::istream& args);
	bool HandleRectangle(std::istream& args);
	bool Help(std::istream& args);

	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	std::vector<std::unique_ptr<IShape>> m_shapes;
	std::vector<std::unique_ptr<ISolidShape>> m_solidShapes;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;

	struct LineArgs
	{
		CPoint fromPoint;
		CPoint toPoint;
		uint32_t outlineColor;
	};

	struct CircleArgs
	{
		CPoint centerPoint;
		uint32_t radius;
		uint32_t outlineColor;
		uint32_t fillColor;
	};

	struct RectangleArgs
	{
		CPoint leftTopPoint;
		uint32_t width;
		uint32_t height;
		uint32_t outlineColor;
		uint32_t fillColor;
	};

	struct TriangleArgs
	{
		CPoint points[3];
		uint32_t outlineColor;
		uint32_t fillColor;
	};

	LineArgs ParseLineArgs(std::istream& args);
	CircleArgs ParseCircleArgs(std::istream& args);
	TriangleArgs ParseTriangleArgs(std::istream& args);
	RectangleArgs ParseRectangleArgs(std::istream& args);
};