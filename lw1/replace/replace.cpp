#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <algorithm>
#include <functional>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchStr;
	std::string replaceStr;
};

std::optional<Args> ParseArgs(int argc, char* argv[]);
bool Replace(const std::string& inputFileName, const std::string& outputFileName,
	const std::string& searchStr, const std::string& replaceStr);

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	if (!Replace(args->inputFileName, args->outputFileName, args->searchStr, args->replaceStr))
	{
		return 1;
	}

	return 0;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage copyfile.exe <inputf file name> <output file name>\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchStr = argv[3];
	args.replaceStr = argv[4];
	return args;
}

std::string ReplaceString(const std::string& str, const std::string& searchStr, const std::string& replaceStr)
{
	if (!searchStr.length())
	{
		return str;
	}

	std::string resultStr;
	auto searchingStartPos = str.begin();
	const std::boyer_moore_searcher searcher(searchStr.begin(), searchStr.end());
	auto it = std::search(searchingStartPos, str.end(), searcher);

	if (it == str.end())
	{
		return str;
	}

	while (it != str.end())
	{
		std::copy(searchingStartPos, it, std::back_inserter(resultStr));
		resultStr.append(replaceStr);
		searchingStartPos = it + searchStr.length();
		it = std::search(searchingStartPos, str.end(), searcher); //searcher
	}
	std::copy(searchingStartPos, str.end(), std::back_inserter(resultStr));
    
	return resultStr;
}

void ReplaceStream(std::ifstream& input, std::ofstream& output, const std::string& searchStr,
	const std::string& replaceStr)
{
	std::string line;
	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchStr, replaceStr);
		if (!input.eof())
		{
			output << std::endl;
		}
	}
}

bool Replace(const std::string& inputFileName, const std::string& outputFileName,
	const std::string& searchStr, const std::string& replaceStr)
{
	std::ifstream input;
	input.open(inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << inputFileName << "' for reading\n";
		return false;
	}

	std::ofstream output;
	output.open(outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open '" << outputFileName << "' for writing\n";
		return false;
	}
	
	ReplaceStream(input, output, searchStr, replaceStr);

	if (input.bad())
	{
		std::cout << "Failed to read data form input file\n";
		return false;
	}

	if (!output.flush())
	{
		std::cout << "Failed to write data to output file\n";
		return false;
	}

	return true;
}
