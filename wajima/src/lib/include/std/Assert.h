#ifndef __ASSERT_H__
#define __ASSERT_H__

#include <std/Exception.h>
#include <std/NotEqualException.h>
#include <sstream>

namespace zefiro_std{

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


	namespace Assert {



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
		void assertEquals(	double expected ,
							double actual ,
							double delta ,
							long lineNumber = Exception::UNKNOWNLINENUMBER,
							std::string  fileName = Exception::UNKNOWNFILENAME );
	}; // namespace Assert

#	define ZEFIRO_STD_ASSERT( condition )\
	(zefiro_std::Assert::assertImplementation((condition),(#condition),\
		__LINE__,__FILE__))

#	define ZEFIRO_STD_ASSERT_MESSAGE( message , condition )\
	(zefiro_std::Assert::assertImplementation( condition, \
												message, \
												__LINE__,\
												__FILE__ ) )
#	define ZEFIRO_STD_ASSERT_EQUAL( expected , actual )\
	(zefiro_std::Assert::assertEquals( (epected),(actual),__LINE__,__FILE__))

#	define ZEFIRO_STD_ASSERT_DOUBLES	_EQUAL( expected , actual , delta )\
	(zefiro_std::Assert::assertEquals( expected , actual , delta , __LINE__ , __FILE__ ))

};	// namespace zefiro_std



#endif //__ASSERT_H__