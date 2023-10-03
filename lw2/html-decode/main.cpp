#include <iostream>
#include <string>
#include "HtmlDecode.h"

using namespace std;

int main()
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