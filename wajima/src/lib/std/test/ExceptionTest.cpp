/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/test/Attic/ExceptionTest.cpp,v 1.6 2002/07/02 17:00:18 ama Exp $
 */

#include <fstream>

#include "std/Exception.h"

#include "std/test/ExceptionTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_stdtest::ExceptionTest );

namespace zefiro_stdtest {
	void ExceptionTest::setUp(){
		_exceptionDefault = new zefiro_std::Exception();
		_exception = new zefiro_std::Exception( MESSAGE , LINENUMBER , FILENAME ); 
	}
	void ExceptionTest::tearDown(){
		delete _exception;
		delete _exceptionDefault;
	}
	void ExceptionTest::testLineNumber(){
		CPPUNIT_ASSERT_EQUAL( LINENUMBER , _exception->lineNumber() );
		CPPUNIT_ASSERT_EQUAL( zefiro_std::Exception::UNKNOWNLINENUMBER , _exceptionDefault->lineNumber() );
	}
	void ExceptionTest::testFileName(){
		CPPUNIT_ASSERT_EQUAL( FILENAME , _exception->fileName() );
		CPPUNIT_ASSERT_EQUAL( zefiro_std::Exception::UNKNOWNFILENAME , _exceptionDefault->fileName() );
	}
	void ExceptionTest::testMessage(){
		CPPUNIT_ASSERT_EQUAL( MESSAGE , std::string(_exception->what()) );
		CPPUNIT_ASSERT_EQUAL( std::string("") , std::string(_exceptionDefault->what()) );
	}
	void ExceptionTest::testClone(){
		zefiro_std::Exception *exception = _exception->clone();
		CPPUNIT_ASSERT_EQUAL( _exception->lineNumber() , exception->lineNumber() );
		CPPUNIT_ASSERT_EQUAL( _exception->fileName() , exception->fileName() );
		CPPUNIT_ASSERT_EQUAL( std::string(_exception->what()) , std::string(exception->what()) );
		delete exception;
	}
	void ExceptionTest::testCopy(){
		zefiro_std::Exception *exception = new zefiro_std::Exception();
		*exception = *_exception;
		CPPUNIT_ASSERT_EQUAL( _exception->lineNumber() , exception->lineNumber() ,  );
		CPPUNIT_ASSERT_EQUAL( _exception->fileName() ,  exception->fileName() );
		CPPUNIT_ASSERT_EQUAL( std::string(_exception->what()) , std::string(exception->what()) );
		delete exception;
	}
	void ExceptionTest::testCopyConstruct(){
		zefiro_std::Exception *exception = new zefiro_std::Exception( *_exception );
		CPPUNIT_ASSERT_EQUAL( _exception->lineNumber() , exception->lineNumber() ,  );
		CPPUNIT_ASSERT_EQUAL( _exception->fileName() ,  exception->fileName() );
		CPPUNIT_ASSERT_EQUAL( std::string(_exception->what()) , std::string(exception->what()) );
		delete exception;
	}
	void ExceptionTest::testType(){
		zefiro_std::Exception::Type *type1 = new zefiro_std::Exception::Type("test");
		zefiro_std::Exception::Type *type2 = new zefiro_std::Exception::Type("test");
		
		CPPUNIT_ASSERT( *type1 == *type2 );

		CPPUNIT_ASSERT( zefiro_std::Exception::Type("zefiro_std::Exception") == zefiro_std::Exception::type() );

		delete type1;
		delete type2;
	}
	void ExceptionTest::testIsInstanceOf(){
		CPPUNIT_ASSERT_EQUAL( true , _exception->isInstanceOf(zefiro_std::Exception::Type("zefiro_std::Exception")) );
	}
};