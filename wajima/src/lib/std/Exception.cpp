#include <std/Exception.h>

namespace zefiro_std {
	const std::string Exception::UNKNOWNFILENAME = "<unknown>";
	const long Exception::UNKNOWNLINENUMBER = -1;
	Exception::Exception( std::string message , long lineNumber , std::string fileName ):_lineNumber(lineNumber),_fileName(fileName),_message(message){
	}
	long Exception::getLineNumber(){
		return _lineNumber;
	}
	std::string Exception::getFileName(){
		return _fileName;
	}
	const char *Exception::what()const throw(){
		return _message.c_str();
	}
	Exception *Exception::clone() const {
		return new Exception( *this );
	}
	Exception& Exception::operator =( const Exception &other ){
		_lineNumber = other._lineNumber;
		_fileName = other._fileName;
		_message = other._message;
		return *this;
	}
	Exception::Type Exception::getType(){
		return Type("zefiro_std::Exception");
	}
	bool Exception::isInstanceOf( const Exception::Type &type )const{
		return Exception::getType() == type;
	}
};