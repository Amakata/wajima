//CUPPA:include=+
#include "graphics/sys/DXAssert.h"
#include "graphics/sys/DXException.h"
//CUPPA:include=-
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <d3d8.h>
//CUPPA:namespace=+
namespace zefiro_graphics {
//CUPPA:namespace=-

class DXAssertTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(DXAssertTest);
//CUPPA:suite=+
  CPPUNIT_TEST(testD3DOK);
  CPPUNIT_TEST_EXCEPTION( testNotAvailable , zefiro_graphics::DXException );
//CUPPA:suite=-
  CPPUNIT_TEST_SUITE_END();
private:

  // your stuff...

public:

  virtual void setUp() { /* initialize */ }
  virtual void tearDown() { /* terminate */ }

//CUPPA:decl=+
  void testD3DOK() {
	  DXASSERT( D3D_OK );
  }
  void testNotAvailable() {
	  DXASSERT( D3DERR_NOTAVAILABLE );
  }
//CUPPA:decl=-
};

}

namespace zefiro_graphics {
//CUPPA:impl=+
//CUPPA:impl=-

CPPUNIT_TEST_SUITE_REGISTRATION(DXAssertTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(DXAssertTest,"zefiro_graphics");

}
