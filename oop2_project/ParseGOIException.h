#pragma once
//---- include section ------
#include <exception>
#include <string>

/*
 * ParseLevelException class
 */
class ParseGOIException : public std::exception
{
public:
	// constructor
	explicit ParseGOIException(const std::string& errorMessage = "") : m_errorMessage(errorMessage) { }
	// message of exception
	virtual const char* what() const noexcept override { return m_errorMessage.c_str(); }
private:
	// error message
	std::string m_errorMessage;
};

