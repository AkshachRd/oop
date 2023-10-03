#include <iostream>
#include <map>
#include <string>
#include <cassert>

using namespace std;

const char HTML_ENTITY_START = '&';
const char HTML_ENTITY_END = ';';

const map<string, char> htmlEntities = { 
    {"&quot;", '"'}, 
    {"&apos;", '\''}, 
    {"&lt;", '<'}, 
    {"&gt;", '>'}, 
    {"&amp;", '&'} 
};

pair<char, size_t> DecodeEntity(const string& encodedStr)
{
    for (const auto& [entity, decodedChar] : htmlEntities)
    {
        if (encodedStr.substr(0, entity.length()) == entity)
        {
            return { decodedChar, entity.length() };
        }
    }

    return { HTML_ENTITY_START, 1 };
}

string HtmlDecode(const string& html)
{
    string result;

    for (size_t pos = 0; pos < html.length();)
    {
        auto ampPos = html.find(HTML_ENTITY_START, pos);
        result.append(html, pos, ampPos - pos);

        if (ampPos < html.length())
        {
            auto [decodedChar, entityLength] = DecodeEntity(html.substr(ampPos));
            result += decodedChar;
            pos = ampPos + entityLength;
        }
        else
        {
            break;
        }
    }

    return result;
}