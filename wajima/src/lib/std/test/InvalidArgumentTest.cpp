/**
 * $Header: 
 */

#include "std/test/InvalidArgumentTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_stdtest::InvalidArgumentTest );

#define FILENAME "test"
#define LINENUMBER 100L

namespace zefiro_stdtest {
	void InvalidArgumentTest::setUp(){
		_invalidArgument = new zefiro_std::InvalidArgument( zefiro_std::SourceLine( FILENAME , LINENUMBER ) );
	}
	void InvalidArgumentTest::tearDown(){
		delete _invalidArgument;
	}
	void InvalidArgumentTest::testLineNumber(){
		CPPUNIT_ASSERT_EQUAL( LINENUMBER , _invalidArgument->lineNumber() );
	}
	void InvalidArgumentTest::testFileName(){
		CPPUNIT_ASSERT_EQUAL( std::string(FILENAME) , _invalidArgument->fileName() );
	}
	void InvalidArgumentTest::testWhat(){
		CPPUNIT_ASSERT_EQUAL( std::string("") , std::string(_invalidArgument->what()) );
	}
	void InvalidArgumentTest::testInstanceOf(){
		CPPUNIT_ASSERT_EQUAL( true , _invalidArgument->isInstanceOf( zefiro_std::Exception::type() ) );
	}
};