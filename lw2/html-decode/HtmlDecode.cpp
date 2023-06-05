#include <iostream>
#include <map>
#include <string>
#include <algorithm>

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


pair<size_t, string> FindHTMLEntity(const string& html, size_t startPos = 0)
{
    string entityStr;

    startPos = html.find(HTML_ENTITY_START, startPos);
    if (startPos == string::npos)
    {
        return { startPos, "" };
    }

    while (html[startPos] != HTML_ENTITY_END)
    {
        entityStr += html[startPos++];

        if (html[startPos] == HTML_ENTITY_START || startPos >= html.length())
        {
            throw exception("HTML entity isn't closed");
        }
    }
    entityStr += ';';
    startPos = startPos - entityStr.length() + 1;

    return { startPos, entityStr };
}

string ReplaceString(const string& str, const string& searchStr, const string& replaceStr)
{
    if (searchStr.empty())
    {
        return str;
    }

    string resultStr;
    string entity;
    auto searchingStartPos = str.find(HTML_ENTITY_START);
    auto replacingPos = str.find(HTML_ENTITY_START);

    if (replacingPos == string::npos)
    {
        return str;
    }

    while (replacingPos != string::npos)
    {
        while (str[replacingPos] != HTML_ENTITY_END) 
        {
            entity.append(str[replacingPos], 1);
        }
        resultStr.append(searchingStartPos, replacingPos);
        resultStr.append(replaceStr);
        searchingStartPos = replacingPos + searchStr.length();
        replacingPos = str.find(HTML_ENTITY_START, searchingStartPos);
    }
    resultStr.append(searchingStartPos, str.end());

    return resultStr;
}

void ReplaceSubstrings(string& subject, const map<string, char>& htmlEntities)
{
    if (subject.empty())
    {
        return;
    }

    size_t startPos = 0;
    do
    {
        auto htmlEntityIt = htmlEntities.find(entityToReplace);
        if (htmlEntityIt == htmlEntities.end())
        {
            throw invalid_argument("Unknown html entity: " + entityToReplace);
        }
        subject.replace(pos, entityToReplace.length(), 1, htmlEntityIt->second); // антибаза
        auto [pos, entityToReplace] = FindHTMLEntity(subject, startPos);
        startPos = pos + 1;
    } while (pos != string::npos);
}

string HtmlDecode(const string& html)
{
    string result = html;

    ReplaceSubstrings(result, htmlEntities);

    return result;
}