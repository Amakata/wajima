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
			zefiro_std::assertImplementation( false , "false" , 1 , __FILE__ );
			failure("");
		}catch( zefiro_std::Exception &e ){
			CPPUNIT_ASSERT_EQUAL(  std::string(__FILE__) , e.getFileName() );
			CPPUNIT_ASSERT_EQUAL( 1L  ,e.getLineNumber() );
		}
		zefiro_std::assertImplementation( true , "true" , __LINE__ , __FILE__ );
	}
	void AssertTest::testAssertNotEqualImplementation(){
		try{
			zefiro_std::assertNotEqualImplementation( "false" , "false" , 1 , __FILE__ );
			failure("");
		}catch( zefiro_std::NotEqualException &e ){
			CPPUNIT_ASSERT_EQUAL( std::string(__FILE__) , e.getFileName()  );
			CPPUNIT_ASSERT_EQUAL( 1L , e.getLineNumber());
		}
		zefiro_std::assertNotEqualImplementation( "false" , "true" , 1 , __FILE__ );
	}
};
