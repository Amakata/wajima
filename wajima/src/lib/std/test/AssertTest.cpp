/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/test/Attic/AssertTest.cpp,v 1.7 2002/04/29 16:29:26 ama Exp $
 */

#include <string>

#include <std/Assert.h>

#include "std/test/AssertTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_stdtest::AssertTest );

namespace zefiro_stdtest {
	void AssertTest::setUp(){
	}
	void AssertTest::tearDown(){
	}
	void AssertTest::testAssertImplementation(){
		try{
			zefiro_std::Assert::assertImplementation( true , "true" , 1 , __FILE__ );
			CPPUNIT_FAIL("");
		}catch( zefiro_std::Exception &e ){
			CPPUNIT_ASSERT_EQUAL(  std::string(__FILE__) , e.fileName() );
			CPPUNIT_ASSERT_EQUAL( 1L  ,e.lineNumber() );
		}
		zefiro_std::Assert::assertImplementation( false , "false" , __LINE__ , __FILE__ );
	}
	void AssertTest::testAssertNotEqualImplementation(){
		try{
			zefiro_std::Assert::assertNotEqualImplementation( "false" , "false" , 1 , __FILE__ );
			CPPUNIT_FAIL("");
		}catch( zefiro_std::NotEqualException &e ){
			CPPUNIT_ASSERT_EQUAL( std::string(__FILE__) , e.fileName()  );
			CPPUNIT_ASSERT_EQUAL( 1L , e.lineNumber());
		}
	}
	void AssertTest::testAssertEqualsTemplate(){
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
	void AssertTest::testAssertDoubleEqualsTemplate(){
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
};
