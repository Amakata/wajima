//CUPPA:include=+
#include "graphics/sys/D3DDevice.h"
//CUPPA:include=-
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

//CUPPA:namespace=+
namespace zefiro_graphics {
//CUPPA:namespace=-

class D3DDeviceTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(D3DDeviceTest);
//CUPPA:suite=+
//CUPPA:suite=-
  CPPUNIT_TEST_SUITE_END();
private:

  // your stuff...

public:

  virtual void setUp() { /* initialize */ }
  virtual void tearDown() { /* terminate */ }

//CUPPA:decl=+
//CUPPA:decl=-
};

}

namespace zefiro_graphics {
//CUPPA:impl=+
//CUPPA:impl=-

CPPUNIT_TEST_SUITE_REGISTRATION(D3DDeviceTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(D3DDeviceTest,"zefiro_graphics");

}
