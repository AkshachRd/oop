#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <algorithm>
#include <limits>

using namespace std;

const int MIN_RADIX = 2;
const int MAX_RADIX = 36;
const char MAX_RADIX_MAX_DIGIT = 'Z';
const int MAX_RADIX_MAX_DIGIT_NUM = 35;

struct Args
{
	int sourceNotation;
	int destinationNotation;
	string value;
};

optional<Args> ParseArgs(int argc, char* argv[]);
string ConvertFromSourceNotationToDestinationNotation(int sourceNotation, int destinationNotation,
	const string& value, bool& wasError);

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	bool wasError = false;

	string resultVal = ConvertFromSourceNotationToDestinationNotation(args->sourceNotation, args->destinationNotation, args->value, wasError);

	if (wasError)
	{
		return 1;
	}

	cout << resultVal;

	return 0;
}

int CharToNum(char ch, bool& wasError)
{
	if (ch >= '0' && ch <= '9')
	{
		return (int)(ch - '0');
	}
	else if (ch >= 'A' && ch <= MAX_RADIX_MAX_DIGIT)
	{
		return (int)(ch + 10 - 'A');
	}
	else
	{
		cout << "Invalid char to num conversation\n";
		cout << "char must be from 0 to 9 and from A to " << MAX_RADIX_MAX_DIGIT << "\n";
		wasError = true;
		return 1;
	}
}

bool IsAddingWouldCauseOverflow(int result, int adding)
{
	if (adding > 0 && result > numeric_limits<int>::max() - adding)
	{
		return true;
	}

	if (adding < 0 && result < numeric_limits<int>::min() - adding)
	{
		return true;
	}

	return false;
}

int StringToInt(const string& str, int radix, bool& wasError)
{
	int resultInt = 0;
	int exp = 0;

	for (int i = str.length() - 1; i >= 0; i--)
	{
		if (str[i] == '-')
		{
			resultInt *= -1;
		}
		else
		{
			int num = CharToNum(str[i], wasError) * (int)pow(radix, exp++);

			if (IsAddingWouldCauseOverflow(resultInt, num))
			{
				cout << "Overflow error\n";
				cout << "<value> is too big\n";
				wasError = true;
				return 1;
			}

			resultInt += num;
		}
	}

	return resultInt;
}

char NumToChar(int num, bool& wasError)
{
	if (num >= 0 && num <= 9)
	{
		return (char)(num + '0');
	}

	if (num <= MAX_RADIX_MAX_DIGIT_NUM)
	{
		return (char)(num - 10 + 'A');
	}
	
	cout << "Invalid num to char conversation\n";
	cout << "num must be from 0 to " << MAX_RADIX_MAX_DIGIT_NUM << "\n";
	wasError = true;
	return '\0';
}

string IntToString(int inputNum, int radix, bool& wasError)
{
	string resultStr = "";
	bool isNegative = inputNum < 0;
	inputNum = abs(inputNum);

	if (inputNum == 0)
	{
		return "0";
	}

	while (inputNum > 0)
	{
		resultStr += NumToChar(inputNum % radix, wasError);
		inputNum /= radix;
	}

	if (isNegative)
	{
		resultStr += '-';
	}

	reverse(resultStr.begin(), resultStr.end());

	return resultStr;
}

bool IsSrcNotationChar(int srcNot, char ch)
{
	return (ch >= '0' && ch < ('0' + srcNot)) ||
		(ch >= 'A' && ch < ('A' + srcNot - 10));
}

bool IsValueInSrcNototation(int srcNot, const string& value)
{
	if (value.empty())
	{
		return false;
	}

	int start = 0;
	if (value[0] == '-')
	{
		if (value.length() == 1)
		{
			return false;
		}

		start = 1;
	}

	for (int i = start; i < value.length(); i++)
	{
		// source
		if (!IsSrcNotationChar(srcNot, value[i]))
		{
			return false;
		}
	}

	return true;
}

bool IsValidValueInput(const string& value, int srcNotation)
{
	if (srcNotation > MAX_RADIX || value.empty())
	{
		return false;
	}

	return IsValueInSrcNototation(srcNotation, value);
}

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage radix.exe <source notation> <destiantion notation> <value>\n";
		return nullopt;
	}

	Args args;
	bool wasError = false;

	args.sourceNotation = StringToInt(argv[1], 10, wasError);
	if (args.sourceNotation < MIN_RADIX || args.sourceNotation > MAX_RADIX || wasError)
	{
		cout << "Invalid argument\n";
		cout << "<source notation> must be from 2 to 36\n";
		return nullopt;
	}

	args.destinationNotation = StringToInt(argv[2], 10, wasError);
	if (args.destinationNotation < MIN_RADIX || args.destinationNotation > MAX_RADIX || wasError)
	{
		cout << "Invalid argument\n";
		cout << "<destiantion notation> must be from 2 to 36\n";
		return nullopt;
	}

	args.value = argv[3];
	if (!IsValidValueInput(args.value, args.sourceNotation))
	{
		cout << "Invalid argument\n";
		cout << "<value> must contain only digits that are in the <source notation> range\n";
		return nullopt;
	}

	return args;
}

string ConvertFromSourceNotationToDestinationNotation(int sourceNotation, int destinationNotation,
	const string& value, bool& wasError)
{	
	int num = StringToInt(value, sourceNotation, wasError);
	string result = IntToString(num, destinationNotation, wasError);

	return result;
}