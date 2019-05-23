#pragma once
//---- include section ------
#include <exception>
#include <string>

/*
 * ParseLevelException class
 */
class ParseLevelException : public std::exception
{
public:
	// constructor
	explicit ParseLevelException(const std::string& errorMessage = "") : m_errorMessage(errorMessage) { }
	// message of exception
	virtual const char* what() const noexcept override { return m_errorMessage.c_str(); }
private:
	// error message
	std::string m_errorMessage;
};

