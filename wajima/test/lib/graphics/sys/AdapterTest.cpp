//CUPPA:include=+
#include "graphics/sys/Adapter.h"
//CUPPA:include=-
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#define ADAPTERNAME		"adaptername"
#define ADAPTERNUMBER	1


//CUPPA:namespace=+
namespace zefiro_graphics {
//CUPPA:namespace=-

class AdapterTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(AdapterTest);
//CUPPA:suite=+
  CPPUNIT_TEST(testGetName);
  CPPUNIT_TEST(testGetAdapterNumber);
  CPPUNIT_TEST(testGetModeVector);
  CPPUNIT_TEST(testToString);
//CUPPA:suite=-
  CPPUNIT_TEST_SUITE_END();
private:

  Adapter	*adapter_;

public:

  virtual void setUp() { adapter_ = new Adapter(ADAPTERNUMBER , ADAPTERNAME );}
  virtual void tearDown() { delete adapter_; }

//CUPPA:decl=+
  void testGetName() {
		CPPUNIT_ASSERT_EQUAL( adapter_->getName() , std::string(ADAPTERNAME) );
  }
  void testGetAdapterNumber() {
		CPPUNIT_ASSERT_EQUAL( adapter_->getAdapterNumber() , ADAPTERNUMBER );
  }
  void AdapterTest::testGetModeVector(){
		adapter_->addMode( zefiro_graphics::Mode( 800 , 600 , 0 , D3DFMT_R8G8B8 ) );
		std::vector<zefiro_graphics::Mode> modes = adapter_->getModeVector();
		CPPUNIT_ASSERT_EQUAL( (UINT)1 , modes.size() );
		CPPUNIT_ASSERT_EQUAL( zefiro_graphics::Mode( 800 , 600 , 0 , D3DFMT_R8G8B8 ).toString() , modes[0].toString() );
  }
  void testToString() {
		adapter_->addMode( zefiro_graphics::Mode( 800 , 600 , 0 , D3DFMT_R8G8B8 ) );
		std::ostringstream oss;
		oss << std::string(ADAPTERNAME) 
			<< std::endl 
			<< zefiro_graphics::Mode( 800 , 600 , 0 , D3DFMT_R8G8B8 ).toString()
			<< std::endl;

		CPPUNIT_ASSERT_EQUAL( oss.str() , adapter_->toString() );
  }
//CUPPA:decl=-
};

}

namespace zefiro_graphics {
//CUPPA:impl=+
//CUPPA:impl=-

CPPUNIT_TEST_SUITE_REGISTRATION(AdapterTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(AdapterTest,"zefiro_graphics");

}
