//CUPPA:include=+
#include "std/sys/Win32Assert.h"
//CUPPA:include=-
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

//CUPPA:namespace=+
namespace zefiro_std {
//CUPPA:namespace=-

class Win32AssertTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Win32AssertTest);
//CUPPA:suite=+
  CPPUNIT_TEST(testErrorSuccess);
  CPPUNIT_TEST_EXCEPTION( testWin32Assert , zefiro_std::Win32Exception );
//CUPPA:suite=-
  CPPUNIT_TEST_SUITE_END();
private:

  // your stuff...
	
public:

  virtual void setUp() { /* initialize */ }
  virtual void tearDown() { /* terminate */ }

//CUPPA:decl=+
  void testErrorSuccess() {
	WIN32ASSERT( ERROR_SUCCESS );
  }
  void testWin32Assert(){
    WIN32ASSERT( 1 );
  }
//CUPPA:decl=-
};

}

namespace zefiro_std {
//CUPPA:impl=+
//CUPPA:impl=-

CPPUNIT_TEST_SUITE_REGISTRATION(Win32AssertTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(Win32AssertTest,"zefiro_std");

}
