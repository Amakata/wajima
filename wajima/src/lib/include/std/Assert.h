#ifndef __ASSERT_H__
#define __ASSERT_H__

#include <std/Exception.h>
#include <std/NotEqualException.h>
#include <sstream>

namespace zefiro_std{
	namespace Assert {

		template <class T>
		struct assertion_traits
		{
			static bool equal( const T& x, const T& y )
			{
				return x == y;
			}

			static std::string toString( const T& x ){
				std::ostringstream oss;
				oss << x;
				return oss.str();
			}
		};

		void assertImplementation( bool         condition, 
			                       std::string  conditionExpression = "",
				                   long lineNumber = Exception::UNKNOWNLINENUMBER,
					               std::string  fileName = Exception::UNKNOWNFILENAME );
		void assertNotEqualImplementation( std::string expected,
			                               std::string actual,
						                   long lineNumber = Exception::UNKNOWNLINENUMBER,
								           std::string  fileName = Exception::UNKNOWNFILENAME );
		template <class T>
		void assertEquals(	const T& expected ,
							const T& actual ,
							long lineNumber = Exception::UNKNOWNLINENUMBER,
							std::string  fileName = Exception::UNKNOWNFILENAME ){
			if( ! assertion_traits<T>::equal( expected , actual ) ){
				assertNotEqualImplementation( assertion_traits<T>::toString(expected) , assertion_traits<T>::toString(actual) , lineNumber , fileName );
			}
		}
	};
};

#endif //__ASSERT_H__