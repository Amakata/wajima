#include <std/test/ExceptionTest.h>
#include <std/Exception.h>

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
		CPPUNIT_ASSERT_EQUAL( LINENUMBER , _exception->getLineNumber() );
		CPPUNIT_ASSERT_EQUAL( zefiro_std::Exception::UNKNOWNLINENUMBER , _exceptionDefault->getLineNumber() );
	}
	void ExceptionTest::testFileName(){
		CPPUNIT_ASSERT_EQUAL( FILENAME , _exception->getFileName() );
		CPPUNIT_ASSERT_EQUAL( zefiro_std::Exception::UNKNOWNFILENAME , _exceptionDefault->getFileName() );
	}
	void ExceptionTest::testMessage(){
		CPPUNIT_ASSERT_EQUAL( MESSAGE , std::string(_exception->what()) );
		CPPUNIT_ASSERT_EQUAL( std::string("") , std::string(_exceptionDefault->what()) );
	}
	void ExceptionTest::testClone(){
		zefiro_std::Exception *exception = _exception->clone();
		CPPUNIT_ASSERT_EQUAL( _exception->getLineNumber() , exception->getLineNumber() );
		CPPUNIT_ASSERT_EQUAL( _exception->getFileName() , exception->getFileName() );
		CPPUNIT_ASSERT_EQUAL( _exception->what() , exception->what() );
		delete exception;
	}
	void ExceptionTest::testCopy(){
		zefiro_std::Exception *exception = new zefiro_std::Exception();
		*exception = *_exception;
		CPPUNIT_ASSERT_EQUAL( _exception->getLineNumber() , exception->getLineNumber() ,  );
		CPPUNIT_ASSERT_EQUAL( _exception->getFileName() ,  exception->getFileName() );
		CPPUNIT_ASSERT_EQUAL( _exception->what() , exception->what() );
		delete exception;
	}
	void ExceptionTest::testCopyConstruct(){
		zefiro_std::Exception *exception = new zefiro_std::Exception( *_exception );
		CPPUNIT_ASSERT_EQUAL( _exception->getLineNumber() , exception->getLineNumber() ,  );
		CPPUNIT_ASSERT_EQUAL( _exception->getFileName() ,  exception->getFileName() );
		CPPUNIT_ASSERT_EQUAL( _exception->what() , exception->what() );
		delete exception;
	}
	void ExceptionTest::testType(){
		zefiro_std::Exception::Type *type1 = new zefiro_std::Exception::Type("test");
		zefiro_std::Exception::Type *type2 = new zefiro_std::Exception::Type("test");
		
		CPPUNIT_ASSERT( *type1 == *type2 );

		CPPUNIT_ASSERT( zefiro_std::Exception::Type("zefiro_std::Exception") == zefiro_std::Exception::getType() );

		delete type1;
		delete type2;
	}
	void ExceptionTest::testIsInstanceOf(){
		CPPUNIT_ASSERT_EQUAL( true , _exception->isInstanceOf(zefiro_std::Exception::Type("zefiro_std::Exception")) );
	}
};