#include <windows.h>
#include "Dictionary.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");

    std::multimap<std::string, std::string> dictionary;

    if (!ParseDictionary(dictionary))
    {
        return 1;
    }

    if (!TranslateWords(dictionary))
    {
        return 1;
    }

    return 0;
}