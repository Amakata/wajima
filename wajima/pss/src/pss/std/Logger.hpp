#pragma once;

// �f�o�b�O�r���h�p
// �f�o�b�O�r���h�ŊO���Ŕz�z�����v���O������log4cxx���g�����ƂŁAApache�ւ̎ӎ����L�q����K�v������B
#ifdef DEBUG

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>

#define LOG4CXX_CONFIGUER(propertyFileName)		::log4cxx::PropertyConfigurator::configure(propertyFileName)
#define	LOG4CXX_LOGGER(packageName)				::log4cxx::Logger::getLogger(packageName)
#define LOG4CXX_LOGGER_PTR						::log4cxx::LoggerPtr

#endif

// �����[�X�r���h�p
// log4cxx���g��Ȃ��̂ŁAApache�ւ̎ӎ����L�q����K�v���Ȃ�
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