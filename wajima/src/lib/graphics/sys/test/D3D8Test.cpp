//CUPPA:include=+
#include "graphics/sys/D3D8.h"
//CUPPA:include=-
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

//CUPPA:namespace=+
namespace zefiro_graphics {
//CUPPA:namespace=-

class D3D8Test : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(D3D8Test);
//CUPPA:suite=+
  CPPUNIT_TEST(testAdapterCount);
  CPPUNIT_TEST(testAdapterModeCount);
  CPPUNIT_TEST(testIsAvailable);
  CPPUNIT_TEST(testGetAdapterVector);
//CUPPA:suite=-
  CPPUNIT_TEST_SUITE_END();
private:
	D3D8 *d3d8_;
  // your stuff...

public:

  virtual void setUp() { d3d8_ = new zefiro_graphics::D3D8(); }
  virtual void tearDown() { delete d3d8_; }

//CUPPA:decl=+
  void testAdapterCount() {
	CPPUNIT_ASSERT( 0 < d3d8_->getAdapterCount() );
  }
  void testAdapterModeCount() {
	for( int i=0 ; i<d3d8_->getAdapterCount() ; ++i ){
		CPPUNIT_ASSERT( 0 < d3d8_->getAdapterModeCount( i ) );
	}
  }
  void testIsAvailable() {
		std::vector<zefiro_graphics::Adapter> adapters = d3d8_->getAdapterVector();
		CPPUNIT_ASSERT( 0 < adapters.size() );
  }
  void testGetAdapterVector() {
		CPPUNIT_ASSERT_EQUAL( true , d3d8_->isAvailable() );
  }
//CUPPA:decl=-
};

}

namespace zefiro_graphics {
//CUPPA:impl=+
//CUPPA:impl=-

CPPUNIT_TEST_SUITE_REGISTRATION(D3D8Test);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(D3D8Test,"zefiro_graphics");

}
