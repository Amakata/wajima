#pragma once

#include <exception>
#include <string>
#include <iostream>
#include <sstream>

// tolua_export
// tolua_begin
namespace pss{
	namespace std{
		class Exception : public ::std::exception {
		public:
// tolua用ダミー
#if 0
			Exception();
			virtual const char* what()const;
			virtual const char* type()const;
			virtual long lineNumber()const;
			virtual ::std::string fileName()const;
			virtual ::std::string traceHistory()const;
			virtual ::std::string traceMessage()const;
			virtual void addTraceHistory( ::std::string traceMessage );
			virtual void setWhat( const ::std::string what );
			virtual  void setFileName( const ::std::string fileName );
			virtual void setLineNumber( long lineNumber );			
#endif	
// tolua_end
			Exception()throw():what_(""),lineNumber_(UNKNOWNLINENUMBER),fileName_(UNKNOWNFILENAME){
			}
			virtual ~Exception(){
			}
			virtual const char* what()const throw(){
				return what_.c_str();
			}
			virtual const char* type()const throw(){
				return typeid(*this).name();
			}
			virtual long lineNumber()const throw(){
				return lineNumber_;
			}
			virtual ::std::string fileName()const throw(){
				return fileName_;
			}
			virtual ::std::string traceHistory()const throw(){
				return traces_;
			}
			virtual ::std::string traceMessage()const throw(){
				::std::ostringstream str;
				str << fileName() << "(" << lineNumber() << ") : " << type() << ": " << what();;
				return str.str();
			}
			virtual void addTraceHistory( ::std::string traceMessage ) throw(){
				traces_ = traces_ + "\n" + traceMessage ;
			}
			virtual void setWhat( const ::std::string what )throw(){
				what_ = what;
			}
			virtual  void setFileName( const ::std::string fileName )throw(){
				fileName_ = fileName;
			}
			virtual void setLineNumber( long lineNumber )throw(){
				lineNumber_ = lineNumber;
			}
// tolua_begin
			static const ::std::string UNKNOWNFILENAME;
			static const long UNKNOWNLINENUMBER;
// tolua_end
		private:
			::std::string what_;
			long lineNumber_;
			::std::string fileName_;
			::std::string traces_;
// tolua_begin
		};
#ifdef PSS_STD_EXCEPTION_COMPILE
		const ::std::string Exception::UNKNOWNFILENAME = "<unknown>";
		const long Exception::UNKNOWNLINENUMBER = -1;
#endif

		template< typename EXCEPTION >
		class Thrower{
		public:
			static void doThrow( ::std::string what ="", long lineNumber = ::pss::std::Exception::UNKNOWNLINENUMBER , ::std::string fileName = ::pss::std::Exception::UNKNOWNFILENAME ){
				EXCEPTION e;
				e.setWhat(what);
				e.setLineNumber(lineNumber);
				e.setFileName(fileName);
				e.addTraceHistory(e.traceMessage());
				throw e;
			}
			static void doThrow( ::std::string what ="", ::std::string traceHistory = "", long lineNumber = ::pss::std::Exception::UNKNOWNLINENUMBER , ::std::string fileName = ::pss::std::Exception::UNKNOWNFILENAME ){
				EXCEPTION e;
				e.setWhat(what);
				e.setLineNumber(lineNumber);
				e.setFileName(fileName);
				e.addTraceHistory(e.traceMessage());
				e.addTraceHistory(traceHistory);
				throw e;		
			}
		};

		template<typename PARAM>
		class ParamException : public Exception {
		public:
			ParamException()throw() :Exception(){
			}
			virtual ~ParamException(){
			}
			virtual void setParam( const PARAM param )throw(){
				param_ = param;
				paramMessage_ = param_.message() +" : "+Exception::what();
			}
			virtual void setWhat( const ::std::string what )throw(){
				Exception::setWhat( what );
				paramMessage_ = param_.message() +" : "+Exception::what();
			}
			virtual PARAM param()const throw(){
				return param_;
			}
			virtual const char* what()const throw(){
				return paramMessage_.c_str();
			}
// tolua_end
		protected:
			::std::string paramMessage_;
			PARAM param_;
// tolua_begin
		};

		class ParamThrower{
		public:
			template<typename PARAM>
				static void doThrow( PARAM param , ::std::string what ="", long lineNumber = ::pss::std::Exception::UNKNOWNLINENUMBER , ::std::string fileName = ::pss::std::Exception::UNKNOWNFILENAME ){	
				::pss::std::ParamException<PARAM> e;
				e.setWhat(what);
				e.setLineNumber(lineNumber);
				e.setFileName(fileName);
				e.setParam(param);		
				e.addTraceHistory(e.traceMessage());
				throw e;
			}
			template<typename PARAM>
				static void doThrow( PARAM param , ::std::string what ="", ::std::string traceHistory ="", long lineNumber = ::pss::std::Exception::UNKNOWNLINENUMBER , ::std::string fileName = ::pss::std::Exception::UNKNOWNFILENAME ){
				::pss::std::ParamException<PARAM> e;
				e.setWhat(what);
				e.setLineNumber(lineNumber);
				e.setFileName(fileName);
				e.setParam(param);
				e.addTraceHistory(e.traceMessage());
				e.addTraceHistory(traceHistory);
				throw e;		
			}
		};


		class SystemException : public ::pss::std::Exception{
		public:
#if 0
			SystemException();
#endif
// tolua_end
			SystemException()throw() :Exception(){
			}
// tolua_begin
			virtual ~SystemException(){
			}
		};
		class LogicException : public ::pss::std::Exception{
		public:
#if 0
			LogicException();
#endif
// tolua_end
			LogicException()throw() :Exception(){
			}
// tolua_begin
			virtual ~LogicException(){
			}
		};

		class NullPointerException : public ::pss::std::Exception{
		public:
#if 0
			NullPointerException();
#endif
// tolua_end
			NullPointerException()throw() :Exception(){
			}
// tolua_begin
			virtual ~NullPointerException(){
			}
		};

		class InvalidArgumentException : public ::pss::std::Exception{
		public:
#if 0
			InvalidArgumentException();
#endif
// tolua_end
			InvalidArgumentException()throw() :Exception(){
			}
// tolua_begin
			virtual ~InvalidArgumentException(){
			}
		};

		class FileNotFoundException : public ::pss::std::Exception{
		public:
#if 0
			FileNotFoundException();
#endif
// tolua_end
			FileNotFoundException()throw() :Exception(){
			}
// tolua_begin
			virtual ~FileNotFoundException(){
			}
		};

	}
}


#define PSS_THROW( EXCEPTION , MESSAGE )	{ ::pss::std::Thrower<EXCEPTION>::doThrow( MESSAGE , __LINE__ , __FILE__ );  }
#define PSS_TRACE_THROW( EXCEPTION , MESSAGE , TRACEEXCEPTION )	{ ::pss::std::Thrower<EXCEPTION>::doThrow( MESSAGE , TRACEEXCEPTION.message() , __LINE__ , __FILE__ ); }
#define PSS_THROW_PARAM1( PARAM , MESSAGE  )	{ ::pss::std::ParamThrower::doThrow( PARAM , MESSAGE , __LINE__ , __FILE__ );  }
#define PSS_TRACE_THROW_PARAM1( PARAM , MESSAGE , TRACEEXCEPTION )	{ ::pss::std::ParamThrower::doThrow( PARAM , MESSAGE , TRACEEXCEPTION.message() , __LINE__ , __FILE__ ); }
// tolua_end
