//CUPPA:include=+
#include "graphics/sys/DXException.h"

#include "std/InvalidArgument.h"

//CUPPA:include=-
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#define HRESULT 1L
#define LINENUMBER 2L
#define FILENAME "test"
#define MESSAGE "[DXException Message]"

//CUPPA:namespace=+
namespace zefiro_graphics {
//CUPPA:namespace=-

class DXExceptionTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(DXExceptionTest);
//CUPPA:suite=+
  CPPUNIT_TEST(testGetHResult);
  CPPUNIT_TEST(testLineNumber);
  CPPUNIT_TEST(testFileName);
  CPPUNIT_TEST(testIsInstanceOf);
  CPPUNIT_TEST(testType);
  CPPUNIT_TEST(testWhat);
//CUPPA:suite=-
  CPPUNIT_TEST_SUITE_END();
private:

  DXException *dxexception_;

public:

  virtual void setUp() { dxexception_ = new DXException( HRESULT , LINENUMBER , FILENAME , MESSAGE ); }
  virtual void tearDown() { delete dxexception_; }

//CUPPA:decl=+
  void testGetHResult() {
		CPPUNIT_ASSERT_EQUAL( HRESULT , dxexception_->getHResult() );
  }
  void testLineNumber() {
		CPPUNIT_ASSERT_EQUAL( LINENUMBER , dxexception_->lineNumber() );
  }
  void testFileName() {
		CPPUNIT_ASSERT_EQUAL( std::string(FILENAME), dxexception_->fileName() );
  }
  void testIsInstanceOf() {
		CPPUNIT_ASSERT( dxexception_->isInstanceOf( zefiro_graphics::DXException::type() ) ); 
		CPPUNIT_ASSERT( dxexception_->isInstanceOf( zefiro_std::Exception::type() ) );
		CPPUNIT_ASSERT( !dxexception_->isInstanceOf( zefiro_std::InvalidArgument::type() ) );
  }
  void testType() {
		CPPUNIT_ASSERT( zefiro_std::Exception::Type("zefiro_graphics::DXException") == zefiro_graphics::DXException::type() );
  }
  void testWhat() {
	  CPPUNIT_ASSERT_EQUAL( std::string(MESSAGE) , std::string(dxexception_->what()) );
  }
//CUPPA:decl=-
};

}

namespace zefiro_graphics {
//CUPPA:impl=+
//CUPPA:impl=-

CPPUNIT_TEST_SUITE_REGISTRATION(DXExceptionTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(DXExceptionTest,"zefiro_graphics");

}
