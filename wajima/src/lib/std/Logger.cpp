/**
 * $Header:
 */

#include "std/logger.h"

#include <fstream>

namespace zefiro_std {
	void Logger::setOutputter( std::ostream *ostr ){
		ostr__ = ostr;
	}
	void Logger::resetOutputter(){
		ostr__ = NULL;
	}
	void Logger::logging( std::string kind , std::string message , SourceLine sourceLine ){
		if( ostr__ == NULL ){
			return;
		}
		*ostr__ <<  sourceLine.fileName() << "(" << sourceLine.lineNumber() << ") : " << kind << " : " << message << std::endl;
		ostr__->flush();
	}
	std::ostream* Logger::ostr__ = NULL;
};