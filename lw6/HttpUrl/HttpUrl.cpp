#include "UrlParsingError.h"
#include "HttpUrl.h"

const std::string URL_REGEX_EXPRESSION = R"(^(https?)://([^/:]+)(?::(\d+))?(.*)$)";
const std::regex HTTP_URL_REG(URL_REGEX_EXPRESSION, std::regex_constants::icase);

const std::string DOMAIN_REGULAR_EXPRESSION = R"(^([\w-]{1,63}(?:\.[\w-]{1,63})*)$)";
const std::regex DOMAIN_REG(DOMAIN_REGULAR_EXPRESSION, std::regex_constants::icase);

const std::string DOCUMENT_REGULAR_EXPRESSION = R"(^(((?:/)*([^\s]*))*)$)";
const std::regex DOCUMENT_REG(DOCUMENT_REGULAR_EXPRESSION, std::regex_constants::icase);

CHttpUrl::CHttpUrl(const std::string& url)
{
    std::smatch matches;

    std::regex_search(url, matches, HTTP_URL_REG);

    if (matches.size() != 5)
    {
        throw CUrlParsingError("invalid url");
    }

    m_domain = matches[2];
    m_document = matches[4].str();
    try
    {
        m_protocol = ParseProtocol(matches[1]);
        m_port = ParsePort(matches[3], m_protocol);
    }
    catch (CUrlParsingError const& error)
    {
        throw error;
    }

    m_url = BuildUrl(m_domain, m_document, m_protocol, m_port);
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol)
{
    m_protocol = protocol;
    try
    {
        m_domain = ParseDomain(domain);
        m_document = ParseDocument(document);
        m_port = ProtocolToDefaultPort(protocol);
    }
    catch (CUrlParsingError const& error)
    {
        throw error;
    }

    m_url = BuildUrl(m_domain, m_document, m_protocol, m_port);
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port)
{
    m_protocol = protocol;
    m_port = port;
    try
    {
        m_domain = ParseDomain(domain);
        m_document = ParseDocument(document);
    }
    catch (CUrlParsingError const& error)
    {
        throw error;
    }

    m_url = BuildUrl(m_domain, m_document, m_protocol, m_port);
}

std::string CHttpUrl::GetURL() const
{
    return m_url;
}

std::string CHttpUrl::GetDomain() const
{
    return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
    return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
    return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
    return m_port;
}

std::string CHttpUrl::BuildUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port)
{
    std::ostringstream urlStream;
    urlStream << GetStrFromProtocol(protocol) << "://" << domain;
    if (port != DEFAULT_HTTP_PORT && port != DEFAULT_HTTPS_PORT)
    {
        urlStream << ':' << port;
    }
    urlStream << document;

    return urlStream.str();
}

std::string CHttpUrl::GetStrFromProtocol(Protocol protocol)
{
    switch (protocol)
    {
    case Protocol::HTTP:
        return "http";
    case Protocol::HTTPS:
        return "https";
    default:
        throw CUrlParsingError("invalid url");
    }
}

Protocol CHttpUrl::ParseProtocol(std::string const& strProtocol)
{
    if (strProtocol == "http")
    {
        return Protocol::HTTP;
    }
    else if (strProtocol == "https")
    {
        return Protocol::HTTPS;
    }
    else
    {
        throw CUrlParsingError("invalid protocol");
    }
};

unsigned short CHttpUrl::ProtocolToDefaultPort(Protocol const& protocol)
{
    return (protocol == Protocol::HTTP) ? DEFAULT_HTTP_PORT : DEFAULT_HTTPS_PORT;
};

unsigned short CHttpUrl::ParsePort(std::string const& strPort, Protocol const& protocol)
{
    if (strPort.length() == 0)
    {
        return ProtocolToDefaultPort(protocol);
    }

    try
    {
        int port = std::stoi(strPort);

        if (port >= MIN_PORT && port <= MAX_PORT)
        {
            return static_cast<unsigned short>(port);
        }
        else
        {
            throw CUrlParsingError("error parsing port");
        }
    }
    catch (const std::exception&)
    {
        throw CUrlParsingError("error parsing port");
    }
};

std::string CHttpUrl::ParseDomain(std::string const& domain)
{
    std::smatch matches;

    if (!regex_search(domain, matches, DOMAIN_REG))
    {
        throw CUrlParsingError("invalid domain");
    }

    return matches[1];
};

std::string CHttpUrl::ParseDocument(std::string const& document)
{
    std::smatch matches;

    if (!std::regex_search(document, matches, DOCUMENT_REG))
    {
        throw CUrlParsingError("invalid document");
    }

    std::string parsedDocument = matches[1];

    if (parsedDocument[0] != '/')
    {
        parsedDocument = '/' + parsedDocument;
    }

    return parsedDocument;
};