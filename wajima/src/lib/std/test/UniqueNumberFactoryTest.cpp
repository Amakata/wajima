//CUPPA:include=+
#include "std/UniqueNumberFactory.h"
//CUPPA:include=-
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <limits>

//CUPPA:namespace=+
namespace zefiro_std {
//CUPPA:namespace=-

class UniqueNumberFactoryTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(UniqueNumberFactoryTest);
//CUPPA:suite=+
  CPPUNIT_TEST(testRepeat);
  CPPUNIT_TEST(testDelete);
  CPPUNIT_TEST_EXCEPTION( testUpperBound , zefiro_std::UniqueNumberBadAlloc );
//CUPPA:suite=-
  CPPUNIT_TEST_SUITE_END();
private:

  // your stuff...
		zefiro_std::UniqueNumberFactory	*_uniqueNumberFactory;
		zefiro_std::UniqueNumberFactory *_uniqueNumberFactoryUpperBound;
public:

  virtual void setUp() {
	_uniqueNumberFactory = new zefiro_std::UniqueNumberFactory();
	_uniqueNumberFactoryUpperBound = new zefiro_std::UniqueNumberFactory(std::numeric_limits<int>::max()-1);
  }
  virtual void tearDown() {
  	delete _uniqueNumberFactoryUpperBound;
  	delete _uniqueNumberFactory;
  }

//CUPPA:decl=+
  void testRepeat() {
		for( int count=0 ; count<10 ; ++count ){
			CPPUNIT_ASSERT( count + 1 == _uniqueNumberFactory->createNumber() );
		}
  }
  void testDelete() {
		int uniqueNumber = _uniqueNumberFactory->createNumber();
		_uniqueNumberFactory->deleteNumber( uniqueNumber );
		CPPUNIT_ASSERT( _uniqueNumberFactory->createNumber() == uniqueNumber );
  }
  void UniqueNumberFactoryTest::testUpperBound(){
		CPPUNIT_ASSERT( _uniqueNumberFactoryUpperBound->createNumber() == std::numeric_limits<int>::max() );
		_uniqueNumberFactoryUpperBound->createNumber();
  }
//CUPPA:decl=-
};

}

namespace zefiro_std {
//CUPPA:impl=+
//CUPPA:impl=-

CPPUNIT_TEST_SUITE_REGISTRATION(UniqueNumberFactoryTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(UniqueNumberFactoryTest,"zefiro_std");

}
