#include <std/test/AssertTest.h>
#include <string>

#include <std/Assert.h>

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_stdtest::AssertTest );

namespace zefiro_stdtest {
	void AssertTest::setUp(){
	}
	void AssertTest::tearDown(){
	}
	void AssertTest::testAssertImplementation(){
		try{
			zefiro_std::Assert::assertImplementation( false , "false" , 1 , __FILE__ );
			failure("");
		}catch( zefiro_std::Exception &e ){
			CPPUNIT_ASSERT_EQUAL(  std::string(__FILE__) , e.getFileName() );
			CPPUNIT_ASSERT_EQUAL( 1L  ,e.getLineNumber() );
		}
		zefiro_std::Assert::assertImplementation( true , "true" , __LINE__ , __FILE__ );
	}
	void AssertTest::testAssertNotEqualImplementation(){
		try{
			zefiro_std::Assert::assertNotEqualImplementation( "false" , "false" , 1 , __FILE__ );
			failure("");
		}catch( zefiro_std::NotEqualException &e ){
			CPPUNIT_ASSERT_EQUAL( std::string(__FILE__) , e.getFileName()  );
			CPPUNIT_ASSERT_EQUAL( 1L , e.getLineNumber());
		}
	}
	void AssertTest::testAssertEqualsTemplate(){
		try{
			zefiro_std::Assert::assertEquals( 100 , -100 , 10L , __FILE__ );
			failure("");
		}catch( zefiro_std::NotEqualException &e ){
			CPPUNIT_ASSERT_EQUAL( std::string(__FILE__) , e.getFileName() );
			CPPUNIT_ASSERT_EQUAL( 10L , e.getLineNumber() );
			CPPUNIT_ASSERT_EQUAL( std::string("100") , e.getExpectedValue() );
			CPPUNIT_ASSERT_EQUAL( std::string("-100") , e.getActualValue() );
		}
		zefiro_std::Assert::assertEquals( 100 , 100 , __LINE__ , __FILE__ );
	}
};
