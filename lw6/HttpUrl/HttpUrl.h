﻿#pragma once
#include <string>
#include <sstream>
#include <regex>

const unsigned short DEFAULT_HTTP_PORT = 80;
const unsigned short DEFAULT_HTTPS_PORT = 443;

const unsigned short MIN_PORT = 0;
const unsigned short MAX_PORT = 65535;


enum class Protocol
{
    HTTP,
    HTTPS
};

class CHttpUrl
{
public:
    CHttpUrl(const std::string& url);
    CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol = Protocol::HTTP);
    CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port);

    std::string GetURL() const;
    std::string GetDomain() const;
    std::string GetDocument() const;
    Protocol GetProtocol() const;
    unsigned short GetPort() const;

private:
    std::string m_url;
    std::string m_domain;
    std::string m_document;
    Protocol m_protocol;
    unsigned short m_port;
};
