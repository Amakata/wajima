//CUPPA:include=+
#include "std/NotEqualException.h"
//CUPPA:include=-
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

//CUPPA:namespace=+
namespace zefiro_std {
//CUPPA:namespace=-

class NotEqualExceptionTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(NotEqualExceptionTest);
//CUPPA:suite=+
  CPPUNIT_TEST(testConstruct);
  CPPUNIT_TEST(testCopyConstruct);
  CPPUNIT_TEST(testCopy);
  CPPUNIT_TEST(testClone);
  CPPUNIT_TEST(testFileName);
  CPPUNIT_TEST(testLineNumber);
  CPPUNIT_TEST(testExceptionValue);
  CPPUNIT_TEST(testActualValue);
  CPPUNIT_TEST(testType);
  CPPUNIT_TEST(testIsInstanceOf);
//CUPPA:suite=-
  CPPUNIT_TEST_SUITE_END();
private:

  // your stuff...
		zefiro_std::NotEqualException *_notEqualException;
public:

  virtual void setUp() {
	_notEqualException = new zefiro_std::NotEqualException( "expected" , "actual" , 1L , __FILE__ );
  }
  virtual void tearDown() {
	delete _notEqualException;
  }

//CUPPA:decl=+
  void testConstruct() {
		zefiro_std::NotEqualException *exception = new zefiro_std::NotEqualException( "expected" , "actual" , __LINE__ , __FILE__ );
		delete exception;
  }
  void testCopyConstruct() {
		zefiro_std::NotEqualException *exception = new zefiro_std::NotEqualException( *_notEqualException );
		CPPUNIT_ASSERT_EQUAL( std::string( __FILE__ ) , exception->fileName() );
		CPPUNIT_ASSERT_EQUAL( 1L , exception->lineNumber() );
		CPPUNIT_ASSERT_EQUAL( std::string( "expected" ) , exception->expectedValue() );
		CPPUNIT_ASSERT_EQUAL( std::string( "actual" ) , exception->actualValue() );
		delete exception;
  }
  void testCopy() {
		zefiro_std::NotEqualException *exception  = new zefiro_std::NotEqualException( "" , "" , 0L , "test" );
		*exception = *_notEqualException;
		CPPUNIT_ASSERT_EQUAL( std::string( __FILE__ ) , exception->fileName() );
		CPPUNIT_ASSERT_EQUAL( 1L , exception->lineNumber() );
		CPPUNIT_ASSERT_EQUAL( std::string( "expected" ) , exception->expectedValue() );
		CPPUNIT_ASSERT_EQUAL( std::string( "actual" ) , exception->actualValue() );
  }
  void testClone() {
		zefiro_std::NotEqualException *exception = dynamic_cast<zefiro_std::NotEqualException *>(_notEqualException->clone());
		CPPUNIT_ASSERT_EQUAL( std::string( __FILE__ ) , exception->fileName() );
		CPPUNIT_ASSERT_EQUAL( 1L , exception->lineNumber() );
		CPPUNIT_ASSERT_EQUAL( std::string( "expected" ) , exception->expectedValue() );
		CPPUNIT_ASSERT_EQUAL( std::string( "actual" ) , exception->actualValue() );
  }
  void testFileName() {
		CPPUNIT_ASSERT_EQUAL( std::string(__FILE__) , _notEqualException->fileName() );
  }
  void testLineNumber() {
		CPPUNIT_ASSERT_EQUAL( 1L , _notEqualException->lineNumber() );
  }
  void testExceptionValue() {
		CPPUNIT_ASSERT_EQUAL( std::string("expected") , _notEqualException->expectedValue() );
  }
  void testActualValue() {
		CPPUNIT_ASSERT_EQUAL( std::string("actual") , _notEqualException->actualValue() );
  }
  void testType() {
		CPPUNIT_ASSERT( zefiro_std::Exception::Type("zefiro_std::NotEqualException") == zefiro_std::NotEqualException::type() );
  }
  void testIsInstanceOf() {
		CPPUNIT_ASSERT_EQUAL( true , _notEqualException->isInstanceOf( zefiro_std::Exception::Type("zefiro_std::NotEqualException") ) );
  }
//CUPPA:decl=-
};

}

namespace zefiro_std {
//CUPPA:impl=+
//CUPPA:impl=-

CPPUNIT_TEST_SUITE_REGISTRATION(NotEqualExceptionTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(NotEqualExceptionTest,"zefiro_std");

}
