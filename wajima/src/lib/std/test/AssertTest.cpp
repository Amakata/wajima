//CUPPA:include=+
#include "std/Assert.h"
//CUPPA:include=-
#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

//CUPPA:namespace=+
namespace zefiro_std {
//CUPPA:namespace=-

class AssertTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(AssertTest);
//CUPPA:suite=+
  CPPUNIT_TEST(testAssertImplementation);
  CPPUNIT_TEST(testAssertNotEqualImplementation);
  CPPUNIT_TEST(testAssertEqualsTemplate);
  CPPUNIT_TEST(testAssertDoubleEqualsTemplate);
//CUPPA:suite=-
  CPPUNIT_TEST_SUITE_END();
private:

  // your stuff...

public:

  virtual void setUp() { /* initialize */ }
  virtual void tearDown() { /* terminate */ }

//CUPPA:decl=+
  void testAssertImplementation() {
		try{
			zefiro_std::Assert::assertImplementation( true , "true" , 1 , __FILE__ );
			CPPUNIT_FAIL("");
		}catch( zefiro_std::Exception &e ){
			CPPUNIT_ASSERT_EQUAL(  std::string(__FILE__) , e.fileName() );
			CPPUNIT_ASSERT_EQUAL( 1L  ,e.lineNumber() );
		}
		zefiro_std::Assert::assertImplementation( false , "false" , __LINE__ , __FILE__ );
  }
  void testAssertNotEqualImplementation() {
		try{
			zefiro_std::Assert::assertNotEqualImplementation( "false" , "false" , 1 , __FILE__ );
			CPPUNIT_FAIL("");
		}catch( zefiro_std::NotEqualException &e ){
			CPPUNIT_ASSERT_EQUAL( std::string(__FILE__) , e.fileName()  );
			CPPUNIT_ASSERT_EQUAL( 1L , e.lineNumber());
		}
  }
  void testAssertEqualsTemplate() {
		try{
			zefiro_std::Assert::assertEquals( 100 , -100 , 10L , __FILE__ );
			CPPUNIT_FAIL("");
		}catch( zefiro_std::NotEqualException &e ){
			CPPUNIT_ASSERT_EQUAL( std::string(__FILE__) , e.fileName() );
			CPPUNIT_ASSERT_EQUAL( 10L , e.lineNumber() );
			CPPUNIT_ASSERT_EQUAL( std::string("100") , e.expectedValue() );
			CPPUNIT_ASSERT_EQUAL( std::string("-100") , e.actualValue() );
		}
		zefiro_std::Assert::assertEquals( 100 , 100 , __LINE__ , __FILE__ );
  }
  void testAssertDoubleEqualsTemplate() {
		try{
			zefiro_std::Assert::assertEquals( 100.0 , -100.0 , 0.1 , 10L , __FILE__ );
			CPPUNIT_FAIL("");
		}catch( zefiro_std::NotEqualException &e ){
			CPPUNIT_ASSERT_EQUAL( std::string(__FILE__) , e.fileName() );
			CPPUNIT_ASSERT_EQUAL( 10L , e.lineNumber() );
			CPPUNIT_ASSERT_EQUAL( std::string("100") , e.expectedValue() );
			CPPUNIT_ASSERT_EQUAL( std::string("-100") , e.actualValue() );
		}
		zefiro_std::Assert::assertEquals( 100.0 , 100.01 , 0.1 ,__LINE__ , __FILE__ );
  }
//CUPPA:decl=-
};

}

namespace zefiro_std {
//CUPPA:impl=+
//CUPPA:impl=-

CPPUNIT_TEST_SUITE_REGISTRATION(AssertTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(AssertTest,"zefiro_std");

}
