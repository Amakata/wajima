//CUPPA:include=+
#include "std/Exception.h"
//CUPPA:include=-
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>

#define LINENUMBER 20L
#define MESSAGE std::string("test-message")
#define FILENAME std::string("test-file")

//CUPPA:namespace=+
namespace zefiro_std {
//CUPPA:namespace=-

class ExceptionTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(ExceptionTest);
//CUPPA:suite=+
  CPPUNIT_TEST(testLineNumber);
  CPPUNIT_TEST(testFileName);
  CPPUNIT_TEST(testMessage);
  CPPUNIT_TEST(testClone);
  CPPUNIT_TEST(testCopy);
  CPPUNIT_TEST(testCopyConstruct);
  CPPUNIT_TEST(testType);
  CPPUNIT_TEST(testIsInstanceOf);
//CUPPA:suite=-
  CPPUNIT_TEST_SUITE_END();
private:

  // your stuff...
	zefiro_std::Exception *_exception;
	zefiro_std::Exception *_exceptionDefault;

public:

  virtual void setUp() {
	_exceptionDefault = new zefiro_std::Exception();
	_exception = new zefiro_std::Exception( MESSAGE , LINENUMBER , FILENAME ); 
  }
  virtual void tearDown() {
	delete _exception;
	delete _exceptionDefault;
  }

//CUPPA:decl=+
  void testLineNumber() {
		CPPUNIT_ASSERT_EQUAL( LINENUMBER , _exception->lineNumber() );
		CPPUNIT_ASSERT_EQUAL( zefiro_std::Exception::UNKNOWNLINENUMBER , _exceptionDefault->lineNumber() );
  }
  void testFileName() {
		CPPUNIT_ASSERT_EQUAL( FILENAME , _exception->fileName() );
		CPPUNIT_ASSERT_EQUAL( zefiro_std::Exception::UNKNOWNFILENAME , _exceptionDefault->fileName() );
  }
  void testMessage() {
		CPPUNIT_ASSERT_EQUAL( MESSAGE , std::string(_exception->what()) );
		CPPUNIT_ASSERT_EQUAL( std::string("") , std::string(_exceptionDefault->what()) );
  }
  void testClone() {
		zefiro_std::Exception *exception = _exception->clone();
		CPPUNIT_ASSERT_EQUAL( _exception->lineNumber() , exception->lineNumber() );
		CPPUNIT_ASSERT_EQUAL( _exception->fileName() , exception->fileName() );
		CPPUNIT_ASSERT_EQUAL( std::string(_exception->what()) , std::string(exception->what()) );
		delete exception;
  }
  void testCopy() {
		zefiro_std::Exception *exception = new zefiro_std::Exception();
		*exception = *_exception;
		CPPUNIT_ASSERT_EQUAL( _exception->lineNumber() , exception->lineNumber() ,  );
		CPPUNIT_ASSERT_EQUAL( _exception->fileName() ,  exception->fileName() );
		CPPUNIT_ASSERT_EQUAL( std::string(_exception->what()) , std::string(exception->what()) );
		delete exception;
  }
  void testCopyConstruct() {
		zefiro_std::Exception *exception = new zefiro_std::Exception( *_exception );
		CPPUNIT_ASSERT_EQUAL( _exception->lineNumber() , exception->lineNumber() ,  );
		CPPUNIT_ASSERT_EQUAL( _exception->fileName() ,  exception->fileName() );
		CPPUNIT_ASSERT_EQUAL( std::string(_exception->what()) , std::string(exception->what()) );
		delete exception;
  }
  void testType() {
		zefiro_std::Exception::Type *type1 = new zefiro_std::Exception::Type("test");
		zefiro_std::Exception::Type *type2 = new zefiro_std::Exception::Type("test");
		
		CPPUNIT_ASSERT( *type1 == *type2 );

		CPPUNIT_ASSERT( zefiro_std::Exception::Type("zefiro_std::Exception") == zefiro_std::Exception::type() );

		delete type1;
		delete type2;
  }
  void testIsInstanceOf() {
		CPPUNIT_ASSERT_EQUAL( true , _exception->isInstanceOf(zefiro_std::Exception::Type("zefiro_std::Exception")) );
  }
//CUPPA:decl=-
};

}

namespace zefiro_std {
//CUPPA:impl=+
//CUPPA:impl=-

CPPUNIT_TEST_SUITE_REGISTRATION(ExceptionTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(ExceptionTest,"zefiro_std");

}
