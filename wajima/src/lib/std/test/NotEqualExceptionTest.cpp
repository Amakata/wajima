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
		CPPUNIT_ASSERT_EQUAL( std::string( __FILE__ ) , exception->getFileName() );
		CPPUNIT_ASSERT_EQUAL( 1L , exception->getLineNumber() );
		CPPUNIT_ASSERT_EQUAL( std::string( "expected" ) , exception->getExpectedValue() );
		CPPUNIT_ASSERT_EQUAL( std::string( "actual" ) , exception->getActualValue() );
		delete exception;
	}
	void NotEqualExceptionTest::testCopy(){
		zefiro_std::NotEqualException *exception  = new zefiro_std::NotEqualException( "" , "" , 0L , "test" );
		*exception = *_notEqualException;
		CPPUNIT_ASSERT_EQUAL( std::string( __FILE__ ) , exception->getFileName() );
		CPPUNIT_ASSERT_EQUAL( 1L , exception->getLineNumber() );
		CPPUNIT_ASSERT_EQUAL( std::string( "expected" ) , exception->getExpectedValue() );
		CPPUNIT_ASSERT_EQUAL( std::string( "actual" ) , exception->getActualValue() );
	}
	void NotEqualExceptionTest::testClone(){
		zefiro_std::NotEqualException *exception = dynamic_cast<zefiro_std::NotEqualException *>(_notEqualException->clone());
		CPPUNIT_ASSERT_EQUAL( std::string( __FILE__ ) , exception->getFileName() );
		CPPUNIT_ASSERT_EQUAL( 1L , exception->getLineNumber() );
		CPPUNIT_ASSERT_EQUAL( std::string( "expected" ) , exception->getExpectedValue() );
		CPPUNIT_ASSERT_EQUAL( std::string( "actual" ) , exception->getActualValue() );

	}
	void NotEqualExceptionTest::testFileName(){
		CPPUNIT_ASSERT_EQUAL( std::string(__FILE__) , _notEqualException->getFileName() );
	}
	void NotEqualExceptionTest::testLineNumber(){
		CPPUNIT_ASSERT_EQUAL( 1L , _notEqualException->getLineNumber() );
	}
	void NotEqualExceptionTest::testExpectedValue(){
		CPPUNIT_ASSERT_EQUAL( std::string("expected") , _notEqualException->getExpectedValue() );
	}
	void NotEqualExceptionTest::testActualValue(){
		CPPUNIT_ASSERT_EQUAL( std::string("actual") , _notEqualException->getActualValue() );
	}
	void NotEqualExceptionTest::testType(){
		CPPUNIT_ASSERT( zefiro_std::Exception::Type("zefiro_std::NotEqualException") == zefiro_std::NotEqualException::getType() );
	}
	void NotEqualExceptionTest::testIsInstanceOf(){
		CPPUNIT_ASSERT_EQUAL( true , _notEqualException->isInstanceOf( zefiro_std::Exception::Type("zefiro_std::NotEqualException") ) );
	}
};