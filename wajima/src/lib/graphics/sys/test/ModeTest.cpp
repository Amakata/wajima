//CUPPA:include=+
#include "graphics/sys/Mode.h"
//CUPPA:include=-
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>


#define MODENUMBER	1
#define WIDTH		800
#define HEIGHT		600
#define REFRESHRATE	0
#define FORMAT	D3DFMT_R8G8B8


//CUPPA:namespace=+
namespace zefiro_graphics {
//CUPPA:namespace=-

class ModeTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(ModeTest);
//CUPPA:suite=+
  CPPUNIT_TEST(testGetModeNumber);
  CPPUNIT_TEST(testGetWidth);
  CPPUNIT_TEST(testGetHeight);
  CPPUNIT_TEST(testGetRefreshRate);
  CPPUNIT_TEST(testGetFormat);
  CPPUNIT_TEST(testToString);
//CUPPA:suite=-
  CPPUNIT_TEST_SUITE_END();
private:
	Mode*	mode_;
  // your stuff...

public:

  virtual void setUp() { mode_ = new Mode( MODENUMBER , WIDTH , HEIGHT , REFRESHRATE , FORMAT ); }
  virtual void tearDown() { delete mode_; }

//CUPPA:decl=+
  void testGetModeNumber() {
	CPPUNIT_ASSERT_EQUAL( MODENUMBER , mode_->getModeNumber() );
  }
  void testGetWidth() {
		CPPUNIT_ASSERT_EQUAL( WIDTH , mode_->getWidth() );
  }
  void testGetHeight() {
		CPPUNIT_ASSERT_EQUAL( HEIGHT , mode_->getHeight() );
  }
  void testGetRefreshRate() {
		CPPUNIT_ASSERT_EQUAL( REFRESHRATE , mode_->getRefreshRate() );
  }
  void testGetFormat() {
		CPPUNIT_ASSERT_EQUAL( FORMAT , mode_->getFormat() );
  }
  void testToString() {
		std::ostringstream oss;
		oss << WIDTH << " " << HEIGHT << " " << REFRESHRATE << " " << FORMAT;
		CPPUNIT_ASSERT_EQUAL( oss.str() , mode_->toString() );
  }
//CUPPA:decl=-
};

}

namespace zefiro_graphics {
//CUPPA:impl=+
//CUPPA:impl=-

CPPUNIT_TEST_SUITE_REGISTRATION(ModeTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(ModeTest,"zefiro_graphics");

}
