#pragma once
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

const std::string ERROR_MSG_DICTIONARY_FILE = "Dictionary file is not entered";
const std::string ERROR_MSG_ANY_LANGUAGES = "В слове используется несколько языков";
const std::string MSG_SAVE_CHANGES = "В слова были внесены изменения. Введите Y или y для сохранения перед выходом.";
const std::string MSG_GOOD_BYE = "Изменения сохранены. До свидания.";

bool ParseDictionary(std::multimap<std::string, std::string>& dictionary);
bool TranslateWords(std::multimap<std::string, std::string>& dictionary);