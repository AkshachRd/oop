#include <iostream>
#include <string>
#include "html-decode.h"

using namespace std;

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