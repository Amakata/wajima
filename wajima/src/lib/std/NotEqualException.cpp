#include <std/NotEqualException.h>

namespace zefiro_std {
	NotEqualException::NotEqualException( std::string expected ,
										  std::string actual ,
										  long lineNumber ,
										  std::string fileName )
										  :Exception( "Expected:" + expected + ",but was: "+actual,lineNumber , fileName),
											_expected(expected),_actual(actual){
	
	}
	Exception *NotEqualException::clone() const {
		return new NotEqualException( *this );
	}
	std::string NotEqualException::getExpectedValue() const {
		return _expected;
	}
	std::string NotEqualException::getActualValue() const {
		return _actual;
	}
	bool NotEqualException::isInstanceOf( Type type ) const {
		return NotEqualException::getType() == type;
	}
	Exception::Type NotEqualException::getType() {
		return "zefiro_std::NotEqualException";
	}

};
