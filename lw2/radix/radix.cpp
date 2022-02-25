#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <algorithm>

using namespace std;

struct Args
{
	string sourceNotation;
	string destinationNotation;
	string value;
};

optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	const string SRC = args->sourceNotation;
	const string DEST = args->destinationNotation;
	const string VALUE = args->value;

	bool wasError = false;



	Replace(args->sourceNotation, args->outputFileName, args->searchStr, args->replaceStr, wasError);

	if (wasError)
	{
		return 1;
	}

	return 0;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage copyfile.exe <inputf file name> <output file name>\n";
		return std::nullopt;
	}
	Args args;
	args.sourceNotation = argv[1];
	args.destinationNotation = argv[2];
	args.value = argv[3];
	return args;
}


int StringToInt(const string& str, bool& wasError)
{
	wasError = false;

	try
	{
		return stoi(str);
	}
	catch (const invalid_argument& err)
	{
		cout << err.what();
		wasError = true;
		return;
	}
	catch (const std::out_of_range& err)
	{
		std::cout << err.what();
		wasError = true;
		return;
	}
	
}

int RadixToDec(const string& value, int radix)
{
	int result;

	return result;
}

std::string ReplaceLine(std::string line, const std::string& searchStr, const std::string& replaceStr)
{
	if (!searchStr.length())
	{
		return line;
	}

	std::string outputStr = "";
	auto lineBegin = line.begin();

	auto it = std::search(lineBegin, line.end(), searchStr.begin(), searchStr.end());

	if (it == line.end())
	{
		return line;
	}

	while (it != line.end())
	{
		std::copy(lineBegin, it, std::back_inserter(outputStr));
		outputStr.append(replaceStr);
		lineBegin = it + searchStr.length();
		it = std::search(lineBegin, line.end(), searchStr.begin(), searchStr.end());
	}
	std::copy(lineBegin, line.end(), std::back_inserter(outputStr));

	return outputStr;
}

void ReplaceStream(std::ifstream& input, std::ofstream& output, const std::string& searchStr,
	const std::string& replaceStr)
{
	std::string line;
	while (std::getline(input, line))
	{
		output << ReplaceLine(line, searchStr, replaceStr);
		if (!input.eof())
		{
			output << std::endl;
		}
	}
}

void Replace(const std::string& inputFileName, const std::string& outputFileName,
	const std::string& searchStr, const std::string& replaceStr, bool& wasError)
{
	std::ifstream input;
	input.open(inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << inputFileName << "' for reading\n";
		wasError = true;
		return;
	}

	std::ofstream output;
	output.open(outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open '" << outputFileName << "' for writing\n";
		wasError = true;
		return;
	}

	ReplaceStream(input, output, searchStr, replaceStr);

	if (input.bad())
	{
		std::cout << "Failed to read data form input file\n";
		wasError = true;
		return;
	}

	if (!output.flush())
	{
		std::cout << "Failed to write data to output file\n";
		wasError = true;
		return;
	}

	return;
}
