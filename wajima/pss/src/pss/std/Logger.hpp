#pragma once;

// デバッグビルド用
// デバッグビルドで外部で配布されるプログラムはlog4cxxを使うことで、Apacheへの謝辞を記述する必要がある。
#ifdef DEBUG

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>

#define LOG4CXX_CONFIGUER(propertyFileName)		::log4cxx::PropertyConfigurator::configure(propertyFileName)
#define	LOG4CXX_LOGGER(packageName)				::log4cxx::Logger::getLogger(packageName)
#define LOG4CXX_LOGGER_PTR						::log4cxx::LoggerPtr

#endif

// リリースビルド用
// log4cxxを使わないので、Apacheへの謝辞を記述する必要がない
#ifdef NDEBUG
namespace pss {
	namespace std {
		class NullLogger {
		public:
			NullLogger() {
			}
		};
	}
}

#define LOG4CXX_CONFIGUER(propertyFileName)
#define	LOG4CXX_LOGGER(packageName)				::pss::std::NullLogger()
#define LOG4CXX_LOGGER_PTR						::pss::std::NullLogger
#define LOG4CXX_DEBUG(logger, message)
#define LOG4CXX_INFO(logger, message) 
#define LOG4CXX_WARN(logger, message) 
#define LOG4CXX_ERROR(logger, message)
#define LOG4CXX_FATAL(logger, message)
#endif