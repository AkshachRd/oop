#include "UrlParsingError.h"

CUrlParsingError::CUrlParsingError(std::string const& error)
	:invalid_argument(error)
{
};