/**
 * $Header: 
 */

#include "std/test/SourceLineTest.h"

#define FILENAME "test"
#define LINENUMBER 100

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_stdtest::SourceLineTest );

namespace zefiro_stdtest {
	void SourceLineTest::setUp(){
		_sourceLineDefault = new zefiro_std::SourceLine();
		_sourceLine = new zefiro_std::SourceLine( FILENAME , LINENUMBER );
	}
	void SourceLineTest::tearDown(){
		delete _sourceLineDefault;
		delete _sourceLine;
	}
	void SourceLineTest::testLineNumber(){
		CPPUNIT_ASSERT_EQUAL( LINENUMBER , _sourceLine->lineNumber() );
		CPPUNIT_ASSERT_EQUAL( -1 , _sourceLineDefault->lineNumber() );
	}
	void SourceLineTest::testFileName(){
		CPPUNIT_ASSERT_EQUAL( std::string(FILENAME) , _sourceLine->fileName() );
		CPPUNIT_ASSERT_EQUAL( std::string("") , _sourceLineDefault->fileName() );
	}
	void SourceLineTest::testIsValid(){
		// ファイル名が""でないかどうかのチェック
		CPPUNIT_ASSERT_EQUAL( true , _sourceLine->isValid() );
		CPPUNIT_ASSERT_EQUAL( false , _sourceLineDefault->isValid() );
	}
	void SourceLineTest::testEqual(){
		CPPUNIT_ASSERT_EQUAL( true , *_sourceLine == *_sourceLine );
		CPPUNIT_ASSERT_EQUAL( true , *_sourceLineDefault == *_sourceLineDefault );
		CPPUNIT_ASSERT_EQUAL( false , *_sourceLineDefault == *_sourceLine );
		CPPUNIT_ASSERT_EQUAL( false , *_sourceLine == *_sourceLineDefault );
	}
	void SourceLineTest::testNotEqual(){
		CPPUNIT_ASSERT_EQUAL( false , *_sourceLine != *_sourceLine );
		CPPUNIT_ASSERT_EQUAL( false, *_sourceLineDefault != *_sourceLineDefault );
		CPPUNIT_ASSERT_EQUAL( true , *_sourceLineDefault != *_sourceLine );
		CPPUNIT_ASSERT_EQUAL( true , *_sourceLine != *_sourceLineDefault );
	}
	void SourceLineTest::testUseCase1(){
		zefiro_std::SourceLine *sourceLine = new zefiro_std::SourceLine();
		CPPUNIT_ASSERT( !sourceLine->isValid() );
		CPPUNIT_ASSERT_EQUAL( std::string("") , sourceLine->fileName() );
		CPPUNIT_ASSERT_EQUAL( -1 , sourceLine->lineNumber() );
		delete sourceLine;
	}
	void SourceLineTest::testUseCase2(){
		zefiro_std::SourceLine *sourceLine = new zefiro_std::SourceLine( FILENAME , LINENUMBER );
		CPPUNIT_ASSERT( sourceLine->isValid() );
		CPPUNIT_ASSERT_EQUAL( std::string(FILENAME) , sourceLine->fileName() );
		CPPUNIT_ASSERT_EQUAL( LINENUMBER , sourceLine->lineNumber() );
		delete sourceLine;		
	}

};