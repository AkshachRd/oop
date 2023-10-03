#include "Dictionary.h"

enum class Language { English, Russian, Other };

bool ParseDictionary(std::multimap<std::string, std::string>& dictionary)
{
	std::ifstream dictionaryFile("dictionary.txt");

	if (!dictionaryFile.is_open())
	{
		std::cout << ERROR_MSG_DICTIONARY_FILE << std::endl;
		return false;
	}

	std::string word, translate;

	while ((dictionaryFile >> word) && (dictionaryFile >> translate))
	{
		dictionary.insert({ word, translate });
	};

	return true;
};

Language DefineLanguage(std::string& word)
{
	auto isRussian = [](char ch) {
		return (ch == '�' || (ch >= '�' && ch <= '�'));
	};

	if (std::all_of(word.begin(), word.end(), isRussian))
	{
		return Language::Russian;
	}
	else if (std::any_of(word.begin(), word.end(), isRussian))
	{
		return Language::Other;
	}
	else
	{
		return Language::English;
	}
};

bool FindEnglishTranslateWord(const std::multimap<std::string, std::string>& dictionary, const std::string& word)
{
	if (dictionary.count(word) == 0)
	{
		return false;
	}

	auto translates = dictionary.equal_range(word);

	for (auto i = translates.first; i != translates.second; ++i)
	{
		if (i != translates.first)
		{
			std::cout << ", ";
		}

		std::cout << i->second;
	}

	std::cout << std::endl;

	return true;
};

bool FindRussianTranslateWord(const std::multimap<std::string, std::string>& dictionary, const std::string& word)
{
	bool transFounded = false;
	bool firstTranslation = true;

	for (auto& infoWord : dictionary)
	{
		if (infoWord.second == word)
		{
			if (!firstTranslation)
			{
				std::cout << ", ";
			}
			else
			{
				firstTranslation = false;
			}
			std::cout << infoWord.first;
			transFounded = true;
		}
	}

	if (transFounded)
	{
		std::cout << std::endl;
	}

	return transFounded;
};

void AddNewEnglishWord(std::multimap<std::string, std::string>& dictionary, std::string& word, bool& isChange)
{
	std::cout << "����������� ����� \"" << word << "\". ������� ������� ��� ������ ������ ��� ������." << std::endl;

	std::string translate;
	getline(std::cin, translate);

	if (translate.length() != 0)
	{
		std::transform(translate.begin(), translate.end(), translate.begin(), tolower);
		dictionary.insert({ word, translate });
		isChange = true;
		std::cout << "����� \"" << word << "\" ��������� � ������� ��� \"" << translate << "\"." << std::endl;
	}
	else
	{
		std::cout << "����� \"" << word << "\" ���������������." << std::endl;
	}
};

void AddNewRussianWord(std::multimap<std::string, std::string>& dictionary, std::string& word, bool& isChange)
{
	std::cout << "����������� ����� \"" << word << "\". ������� ������� ��� ������ ������ ��� ������." << std::endl;

	std::string translate;
	getline(std::cin, translate);

	if (translate.length() != 0)
	{
		std::transform(translate.begin(), translate.end(), translate.begin(), tolower);
		dictionary.insert({ translate, word });
		isChange = true;
		std::cout << "����� \"" << word << "\" ��������� � ������� ��� \"" << translate << "\"." << std::endl;
	}
	else
	{
		std::cout << "����� \"" << word << "\" ���������������." << std::endl;
	}
};

void Translate(std::multimap<std::string, std::string>& dictionary, std::string& word, bool& isChange)
{
	std::transform(word.begin(), word.end(), word.begin(), tolower);
	Language language = DefineLanguage(word);

	switch (language)
	{
	case Language::English:
		if (!FindEnglishTranslateWord(dictionary, word))
		{
			AddNewEnglishWord(dictionary, word, isChange);
		}
		break;
	case Language::Russian:
		if (!FindRussianTranslateWord(dictionary, word))
		{
			AddNewRussianWord(dictionary, word, isChange);
		}
		break;
	case Language::Other:
		std::cout << ERROR_MSG_ANY_LANGUAGES << std::endl;
		break;
	default:
		break;
	}
};

bool SaveWords(const std::multimap<std::string, std::string>& dictionary)
{
	std::ofstream dictionaryFile("dictionary.txt");

	if (!dictionaryFile.is_open())
	{
		std::cout << ERROR_MSG_DICTIONARY_FILE << std::endl;
		return false;
	}

	for (auto infoWord : dictionary)
	{
		dictionaryFile << infoWord.first << " " << infoWord.second << std::endl;
	}
};

bool TranslateWords(std::multimap<std::string, std::string>& dictionary)
{
	std::string word;
	bool isChange = false;

	while (getline(std::cin, word))
	{
		if (word == "...")
		{
			break;
		}

		Translate(dictionary, word, isChange);
	}

	if (isChange)
	{
		std::cout << MSG_SAVE_CHANGES << std::endl;

		getline(std::cin, word);

		if (word == "Y" || word == "y")
		{
			if (!SaveWords(dictionary))
			{
				return false;
			}
			else
			{
				std::cout << MSG_GOOD_BYE << std::endl;
			}
		}
	}

	return true;
};