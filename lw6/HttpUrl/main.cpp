#include <iostream>
#include "HttpUrl.h"
#include "UrlParsingError.h"
#include <string>

int main()
{
    try
    {
        CHttpUrl httpUrl("http://hello.com:85/hello.html");
        std::cout << "URL: " << httpUrl.GetURL() << std::endl;
        std::cout << "Domain: " << httpUrl.GetDomain() << std::endl;
        std::cout << "Document: " << httpUrl.GetDocument() << std::endl;
        std::cout << "Protocol: " << ((httpUrl.GetProtocol() == Protocol::HTTP) ? "HTTP" : "HTTPS") << std::endl;
        std::cout << "Port: " << httpUrl.GetPort() << std::endl;
    }
    catch (const CUrlParsingError& ex)
    {
        std::cout << "Error parsing URL: " << ex.what() << std::endl;
    }

    return 0;
}