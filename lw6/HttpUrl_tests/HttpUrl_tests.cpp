#include "../../catch2/catch.hpp"	
#include "../HttpUrl/HttpUrl.h"

const std::string VALID_STR_URL = "http://hello.com:85/hello.html";
const std::string VALID_STR_URL2 = "https://hello.com/hello.html";
const std::string VALID_STR_URL3 = "http://hello.com/hello.html";
const std::string VALID_STR_URL4 = "https://hello.com/hello.html";
const std::string VALID_STR_URL_DOMAIN = "hello.com";
const unsigned short VALID_STR_URL_PORT = 85;
const std::string VALID_STR_URL_DOCUMENT = "/hello.html";
const std::string DOCUMENT_WITHOUT_SLASH = "hello.html";

TEST_CASE("Valid initialization check")
{
	CHttpUrl validUrl1(VALID_STR_URL);

	REQUIRE(validUrl1.GetURL() == VALID_STR_URL);
	REQUIRE(validUrl1.GetProtocol() == Protocol::HTTP);
	REQUIRE(validUrl1.GetDomain() == VALID_STR_URL_DOMAIN);
	REQUIRE(validUrl1.GetPort() == VALID_STR_URL_PORT);
	REQUIRE(validUrl1.GetDocument() == VALID_STR_URL_DOCUMENT);

	CHttpUrl validUrl2(VALID_STR_URL_DOMAIN, VALID_STR_URL_DOCUMENT, Protocol::HTTPS);

	REQUIRE(validUrl2.GetURL() == VALID_STR_URL2);
	REQUIRE(validUrl2.GetProtocol() == Protocol::HTTPS);
	REQUIRE(validUrl2.GetDomain() == VALID_STR_URL_DOMAIN);
	REQUIRE(validUrl2.GetPort() == DEFAULT_HTTPS_PORT);
	REQUIRE(validUrl2.GetDocument() == VALID_STR_URL_DOCUMENT);

	CHttpUrl validUrl3(VALID_STR_URL_DOMAIN, DOCUMENT_WITHOUT_SLASH, Protocol::HTTP, VALID_STR_URL_PORT);

	REQUIRE(validUrl3.GetURL() == VALID_STR_URL);
	REQUIRE(validUrl3.GetProtocol() == Protocol::HTTP);
	REQUIRE(validUrl3.GetDomain() == VALID_STR_URL_DOMAIN);
	REQUIRE(validUrl3.GetPort() == VALID_STR_URL_PORT);
	REQUIRE(validUrl3.GetDocument() == VALID_STR_URL_DOCUMENT);

	CHttpUrl validUrl4(VALID_STR_URL_DOMAIN, VALID_STR_URL_DOCUMENT, Protocol::HTTP);

	REQUIRE(validUrl4.GetURL() == VALID_STR_URL3);
	REQUIRE(validUrl4.GetProtocol() == Protocol::HTTP);
	REQUIRE(validUrl4.GetDomain() == VALID_STR_URL_DOMAIN);
	REQUIRE(validUrl4.GetPort() == DEFAULT_HTTP_PORT);
	REQUIRE(validUrl4.GetDocument() == VALID_STR_URL_DOCUMENT);

	CHttpUrl validUrl5(VALID_STR_URL4);

	REQUIRE(validUrl5.GetURL() == VALID_STR_URL4);
	REQUIRE(validUrl5.GetProtocol() == Protocol::HTTPS);
	REQUIRE(validUrl5.GetDomain() == VALID_STR_URL_DOMAIN);
	REQUIRE(validUrl5.GetPort() == DEFAULT_HTTPS_PORT);
	REQUIRE(validUrl5.GetDocument() == VALID_STR_URL_DOCUMENT);
};

TEST_CASE("Invalid initialization check")
{
	try
	{
		CHttpUrl invalidUrl("httpp://hello.com:90/hello.txt");
	}
	catch (const std::exception& e)
	{
		std::string textError = e.what();
		REQUIRE(textError == "invalid url");
	}

	try
	{
		CHttpUrl invalidUrl("http://hello.com:90000/hello.txt");
	}
	catch (const std::exception& e)
	{
		std::string textError = e.what();
		REQUIRE(textError == "error parsing port");
	}

	try
	{
		CHttpUrl invalidUrl("", "hello.txt");
	}
	catch (const std::exception& e)
	{
		std::string textError = e.what();
		REQUIRE(textError == "invalid domain");
	}

	try
	{
		CHttpUrl invalidUrl("fe\\", "hello.txt");
	}
	catch (const std::exception& e)
	{
		std::string textError = e.what();
		REQUIRE(textError == "invalid domain");
	}

	try
	{
		CHttpUrl invalidUrl("127.0.0.1", "he llo.txt", Protocol::HTTP, 50);
	}
	catch (const std::exception& e)
	{
		std::string textError = e.what();
		REQUIRE(textError == "invalid document");
	}
};