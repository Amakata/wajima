#include <std/Assert.h>
#include <cmath>

namespace zefiro_std {
	namespace Assert {
		void assertImplementation( bool         condition,
								std::string  conditionExpression ,
								long lineNumber , 
								std::string  fileName ){
			if( !condition ){
				throw Exception( conditionExpression , lineNumber , fileName );
			}

		}
		void assertNotEqualImplementation( std::string expected,
		                                   std::string actual,
			                               long lineNumber ,
										   std::string  fileName ){
			throw NotEqualException( expected , actual , lineNumber , fileName );
		}
		void assertEquals(	double expected ,
							double actual ,
							double delta ,
							long lineNumber ,
							std::string  fileName ){
			if( fabs( expected - actual ) > delta ){
				assertNotEqualImplementation( assertion_traits<double>::toString(expected) , assertion_traits<double>::toString(actual) , lineNumber , fileName );
			}
		}
	};
};