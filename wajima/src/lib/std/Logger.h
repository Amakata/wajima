#ifndef __LOGGER_H__
#define __LOGGER_H__

/**
 * $Header:
 */

#include <iostream>
#include <string>

#include "SourceLine.h"

namespace zefiro_std {
	class Logger
	{
	public:
		static void setOutputter( std::ostream *ostr );
		static void resetOutputter();
		static void logging( std::string kind , std::string message , SourceLine sourceLine  );
	private:
		static std::ostream *ostr__;
	};
};

#define ZEFIRO_LOG( kind , message ) zefiro_std::Logger::logging( kind , message , ZEFIRO_STD_SOURCELINE() )

#endif //__LOGGER_H__