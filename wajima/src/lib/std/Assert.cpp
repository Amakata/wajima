#include <std/Assert.h>

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
	};
};