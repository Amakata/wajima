#ifndef __ASSERT_H__
#define __ASSERT_H__

#include <std/Exception.h>
#include <std/NotEqualException.h>

namespace zefiro_std{
	void assertImplementation( bool         condition, 
                               std::string  conditionExpression = "",
                               long lineNumber = Exception::UNKNOWNLINENUMBER,
                               std::string  fileName = Exception::UNKNOWNFILENAME );
	void assertNotEqualImplementation( std::string expected,
                                       std::string actual,
                               long lineNumber = Exception::UNKNOWNLINENUMBER,
                               std::string  fileName = Exception::UNKNOWNFILENAME );
};

#endif //__ASSERT_H__