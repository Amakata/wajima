//CUPPA:include=+
#include "std/InvalidArgument.h"
//CUPPA:include=-
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>


#define FILENAME "test"
#define LINENUMBER 100L


//CUPPA:namespace=+
namespace zefiro_std {
//CUPPA:namespace=-

class InvalidArgumentTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(InvalidArgumentTest);
//CUPPA:suite=+
  CPPUNIT_TEST(testLineNumber);
  CPPUNIT_TEST(testFileName);
  CPPUNIT_TEST(testWhat);
  CPPUNIT_TEST(testInstanceOf);
//CUPPA:suite=-
  CPPUNIT_TEST_SUITE_END();
private:

  // your stuff...
		zefiro_std::InvalidArgument *_invalidArgument;

public:

  virtual void setUp() {
	_invalidArgument = new zefiro_std::InvalidArgument( zefiro_std::SourceLine( FILENAME , LINENUMBER ) );
  }
  virtual void tearDown() {
	delete _invalidArgument;
  }
//CUPPA:decl=+
  void testLineNumber() {
		CPPUNIT_ASSERT_EQUAL( LINENUMBER , _invalidArgument->lineNumber() );
  }
  void testFileName() {
		CPPUNIT_ASSERT_EQUAL( std::string(FILENAME) , _invalidArgument->fileName() );
  }
  void testWhat() {
		CPPUNIT_ASSERT_EQUAL( std::string("") , std::string(_invalidArgument->what()) );
  }
  void testInstanceOf() {
		CPPUNIT_ASSERT_EQUAL( true , _invalidArgument->isInstanceOf( zefiro_std::Exception::type() ) );
  }
//CUPPA:decl=-
};

}

namespace zefiro_std {
//CUPPA:impl=+
//CUPPA:impl=-

CPPUNIT_TEST_SUITE_REGISTRATION(InvalidArgumentTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(InvalidArgumentTest,"zefiro_std");

}
