#include <std/Exception.h>
#include <string>

namespace zefiro_std {
	class NotEqualException : public Exception
	{
	public:
		NotEqualException( std::string expected,
                           std::string actual,
                           long lineNumber, 
                           std::string fileName );
		Exception *clone() const;
		std::string getExpectedValue() const;
		std::string getActualValue() const;
		bool isInstanceOf( Type type ) const;
		static Exception::Type getType();
	protected:
		std::string _expected;
		std::string _actual;
	};
};