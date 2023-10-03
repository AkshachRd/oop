#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../html-decode/HtmlDecode.h"

SCENARIO("Decode Lines")
{
	std::string output;
	WHEN("Line is empty")
	{
		THEN("Line doesn't change")
		{
			std::string input("");
			output = HtmlDecode(input);
			REQUIRE(output == "");
		}
	}
	WHEN("There is no HTML entities")
	{
		THEN("Line doesn't change")
		{
			std::string input("There are no html entities");
			output = HtmlDecode(input);
			REQUIRE(output == "There are no html entities");
		}
	}
	WHEN("There is 1 html entity in a string: &lt;h1&gt;")
	{
		THEN("There is 1 html tag in ostream: <h1>")
		{
			std::string input("&lt;h1&gt;Hello World!&lt;/h1&gt;");
			output = HtmlDecode(input);
			REQUIRE(output == "<h1>Hello World!</h1>");
		}
	}
	WHEN("There are several html entities in a string: &lt;&lt;&lt;It workes&gt;&gt;&gt;")
	{
		THEN("There are several html entities in a string: <<<It workes>>>")
		{
			std::string input("&lt;&lt;&lt;It workes&gt;&gt;&gt;");
			output = HtmlDecode(input);
			REQUIRE(output == "<<<It workes>>>");
		}
	}
	WHEN("There are several html entities with single & in the input string: &lt;&lt;&lt;& - this is single amp&gt;&gt;&gt;")
	{
		THEN("There are several html entities with single & in the output string: <<<& - this is single amp>>>")
		{
			std::string input("&lt;&lt;&lt;& - this is single amp&gt;&gt;&gt;");
			output = HtmlDecode(input);
			REQUIRE(output == "<<<& - this is single amp>>>");
		}
	}
	WHEN("There are several lines in the input string")
	{
		THEN("Several lines in the output string")
		{
			std::string input("&lt;h1&gt;Hello World!&lt;/h1&gt;\n&lt;h2&gt;It workes!&lt;/h2&gt;");
			output = HtmlDecode(input);
			REQUIRE(output == "<h1>Hello World!</h1>\n<h2>It workes!</h2>");
		}
	}
}