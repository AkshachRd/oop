#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

const char HTML_ENTITY_START = '&';
const char HTML_ENTITY_END = ';';

pair<size_t, string> FindHTMLEntity(const string& subject, size_t pos = 0)
{
    string entityStr;

    pos = subject.find(HTML_ENTITY_START, pos);
    if (pos == string::npos)
    {
        return {pos, ""};
    }

    while (subject[pos] != HTML_ENTITY_END)
    {
        entityStr += subject[pos++];

        if (subject[pos] == HTML_ENTITY_START || pos >= subject.length())
        {
            throw exception("HTML entity isn't closed");
        }
    }
    entityStr += ';';

    return {pos - entityStr.length() + 1, entityStr};
}

void ReplaceSubstrings(string& subject, const map<string, char>& htmlEntities)
{
    if (subject.empty())
    {
        return;
    }

    size_t pos = 0;
    string search;
    tie(pos, search) = FindHTMLEntity(subject);
    
    while (pos != string::npos)
    {
        auto htmlEntitySearch = htmlEntities.find(search);
        if (htmlEntitySearch == htmlEntities.end())
        {
            throw invalid_argument("Unknown html entity: " + search);
        }
        subject.replace(pos++, search.length(), 1, htmlEntitySearch->second);
        tie(pos, search) = FindHTMLEntity(subject, pos);
    }
}

string HtmlDecode(const string& html)
{
    string result = html;

    map<string, char> htmlEntities = { {"&quot;", '"'}, {"&apos;", '\''}, {"&lt;", '<'}, {"&gt;", '>'}, {"&amp;", '&'} };
    ReplaceSubstrings(result, htmlEntities);

    return result;
}

int main()
{
    try
    {
        //string s = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
        string line;
        while (getline(cin, line))
        {
            cout << HtmlDecode(line);
            if (cin.good())
            {
                cout << endl;
            }
        }
    }
    catch (exception e)
    {
        cout << e.what() << endl;
    }
}