#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <exception>
#include <string>

namespace zefiro_std {
	class Exception : public std::exception
	{
	public:
		class Type
		{
		public:
			Type( std::string type ):_type(type){
			}
			bool operator==( const Type & other ) const{
				return _type == other._type;
			}
		private:
			const std::string _type;
		};
		Exception::Exception( std::string message = "" , long lineNumber =  UNKNOWNLINENUMBER , std::string fileName = UNKNOWNFILENAME );
		long getLineNumber();
		std::string getFileName();
		const char *what() const throw();
		virtual Exception *clone() const;
		Exception & operator= (const Exception& other );
		virtual bool isInstanceOf( const Type &type ) const;
		static Type getType();
		static const std::string	UNKNOWNFILENAME;
		static const long			UNKNOWNLINENUMBER;
	protected:
		long _lineNumber;
		std::string _fileName;
		std::string _message;
	};
};

#endif //__EXCEPTION_H__