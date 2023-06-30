#pragma once
#include <string>
#include <regex>
#include <sstream>
#include <cassert>

const unsigned short DEFAULT_HTTP_PORT = 80;
const unsigned short DEFAULT_HTTPS_PORT = 443;

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
    void ParseUrl(const std::string& url);
    Protocol ParseProtocol(std::string const& strProtocol);
    unsigned short ParsePort(std::string const& strPort);
    std::string ParseDomain(std::string const& domain);
    std::string ParseDocument(std::string const& document);
    std::string GetStrFromProtocol(Protocol protocol) const;
    unsigned short ProtocolToDefaultPort(Protocol const& protocol) const;
    void Initialize(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port);

    std::string m_url;
    std::string m_domain;
    std::string m_document;
    Protocol m_protocol;
    unsigned short m_port;
};
