#include <std/test/NotEqualExceptionTest.h>

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_stdtest::NotEqualExceptionTest );

namespace zefiro_stdtest {
	void NotEqualExceptionTest::setUp(){
		_notEqualException = new zefiro_std::NotEqualException( "expected" , "actual" , 1L , __FILE__ );
	}
	void NotEqualExceptionTest::tearDown(){
		delete _notEqualException;
	}
	void NotEqualExceptionTest::testConstruct(){
		zefiro_std::NotEqualException *exception = new zefiro_std::NotEqualException( "expected" , "actual" , __LINE__ , __FILE__ );
		delete exception;
	}
	void NotEqualExceptionTest::testCopyConstruct(){
		zefiro_std::NotEqualException *exception = new zefiro_std::NotEqualException( *_notEqualException );
		CPPUNIT_ASSERT_EQUAL( std::string( __FILE__ ) , exception->fileName() );
		CPPUNIT_ASSERT_EQUAL( 1L , exception->lineNumber() );
		CPPUNIT_ASSERT_EQUAL( std::string( "expected" ) , exception->expectedValue() );
		CPPUNIT_ASSERT_EQUAL( std::string( "actual" ) , exception->actualValue() );
		delete exception;
	}
	void NotEqualExceptionTest::testCopy(){
		zefiro_std::NotEqualException *exception  = new zefiro_std::NotEqualException( "" , "" , 0L , "test" );
		*exception = *_notEqualException;
		CPPUNIT_ASSERT_EQUAL( std::string( __FILE__ ) , exception->fileName() );
		CPPUNIT_ASSERT_EQUAL( 1L , exception->lineNumber() );
		CPPUNIT_ASSERT_EQUAL( std::string( "expected" ) , exception->expectedValue() );
		CPPUNIT_ASSERT_EQUAL( std::string( "actual" ) , exception->actualValue() );
	}
	void NotEqualExceptionTest::testClone(){
		zefiro_std::NotEqualException *exception = dynamic_cast<zefiro_std::NotEqualException *>(_notEqualException->clone());
		CPPUNIT_ASSERT_EQUAL( std::string( __FILE__ ) , exception->fileName() );
		CPPUNIT_ASSERT_EQUAL( 1L , exception->lineNumber() );
		CPPUNIT_ASSERT_EQUAL( std::string( "expected" ) , exception->expectedValue() );
		CPPUNIT_ASSERT_EQUAL( std::string( "actual" ) , exception->actualValue() );

	}
	void NotEqualExceptionTest::testFileName(){
		CPPUNIT_ASSERT_EQUAL( std::string(__FILE__) , _notEqualException->fileName() );
	}
	void NotEqualExceptionTest::testLineNumber(){
		CPPUNIT_ASSERT_EQUAL( 1L , _notEqualException->lineNumber() );
	}
	void NotEqualExceptionTest::testExpectedValue(){
		CPPUNIT_ASSERT_EQUAL( std::string("expected") , _notEqualException->expectedValue() );
	}
	void NotEqualExceptionTest::testActualValue(){
		CPPUNIT_ASSERT_EQUAL( std::string("actual") , _notEqualException->actualValue() );
	}
	void NotEqualExceptionTest::testType(){
		CPPUNIT_ASSERT( zefiro_std::Exception::Type("zefiro_std::NotEqualException") == zefiro_std::NotEqualException::type() );
	}
	void NotEqualExceptionTest::testIsInstanceOf(){
		CPPUNIT_ASSERT_EQUAL( true , _notEqualException->isInstanceOf( zefiro_std::Exception::Type("zefiro_std::NotEqualException") ) );
	}
};