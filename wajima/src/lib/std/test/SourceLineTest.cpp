//CUPPA:include=+
#include "std/SourceLine.h"
//CUPPA:include=-
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#define FILENAME "test"
#define LINENUMBER 100

//CUPPA:namespace=+
namespace zefiro_std {
//CUPPA:namespace=-

class SourceLineTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(SourceLineTest);
//CUPPA:suite=+
  CPPUNIT_TEST(testLineNumber);
  CPPUNIT_TEST(testFileName);
  CPPUNIT_TEST(testIsValid);
  CPPUNIT_TEST(testEqual);
  CPPUNIT_TEST(testNotEqual);
  CPPUNIT_TEST(testUseCase1);
  CPPUNIT_TEST(testUseCase2);
//CUPPA:suite=-
  CPPUNIT_TEST_SUITE_END();
private:

  // your stuff...
		zefiro_std::SourceLine *_sourceLine;
		zefiro_std::SourceLine *_sourceLineDefault;

public:

  virtual void setUp() {
	_sourceLineDefault = new zefiro_std::SourceLine();
	_sourceLine = new zefiro_std::SourceLine( FILENAME , LINENUMBER );
  }
  virtual void tearDown() {
	delete _sourceLineDefault;
	delete _sourceLine;
 }

//CUPPA:decl=+
  void testLineNumber() {
	CPPUNIT_ASSERT_EQUAL( LINENUMBER , _sourceLine->lineNumber() );
	CPPUNIT_ASSERT_EQUAL( -1 , _sourceLineDefault->lineNumber() );
  }
  void testFileName() {
	CPPUNIT_ASSERT_EQUAL( std::string(FILENAME) , _sourceLine->fileName() );
	CPPUNIT_ASSERT_EQUAL( std::string("") , _sourceLineDefault->fileName() );
  }
  void testIsValid() {
	// ファイル名が""でないかどうかのチェック
	CPPUNIT_ASSERT_EQUAL( true , _sourceLine->isValid() );
	CPPUNIT_ASSERT_EQUAL( false , _sourceLineDefault->isValid() );
  }
  void testEqual() {
	CPPUNIT_ASSERT_EQUAL( true , *_sourceLine == *_sourceLine );
	CPPUNIT_ASSERT_EQUAL( true , *_sourceLineDefault == *_sourceLineDefault );
	CPPUNIT_ASSERT_EQUAL( false , *_sourceLineDefault == *_sourceLine );
	CPPUNIT_ASSERT_EQUAL( false , *_sourceLine == *_sourceLineDefault );
  }
  void testNotEqual() {
	CPPUNIT_ASSERT_EQUAL( false , *_sourceLine != *_sourceLine );
	CPPUNIT_ASSERT_EQUAL( false, *_sourceLineDefault != *_sourceLineDefault );
	CPPUNIT_ASSERT_EQUAL( true , *_sourceLineDefault != *_sourceLine );
	CPPUNIT_ASSERT_EQUAL( true , *_sourceLine != *_sourceLineDefault );
  }		
  void testUseCase1() {
		zefiro_std::SourceLine *sourceLine = new zefiro_std::SourceLine();
		CPPUNIT_ASSERT( !sourceLine->isValid() );
		CPPUNIT_ASSERT_EQUAL( std::string("") , sourceLine->fileName() );
		CPPUNIT_ASSERT_EQUAL( -1 , sourceLine->lineNumber() );
		delete sourceLine;
  }
  void testUseCase2() {
		zefiro_std::SourceLine *sourceLine = new zefiro_std::SourceLine( FILENAME , LINENUMBER );
		CPPUNIT_ASSERT( sourceLine->isValid() );
		CPPUNIT_ASSERT_EQUAL( std::string(FILENAME) , sourceLine->fileName() );
		CPPUNIT_ASSERT_EQUAL( LINENUMBER , sourceLine->lineNumber() );
		delete sourceLine;		
  }
//CUPPA:decl=-
};

}

namespace zefiro_std {
//CUPPA:impl=+
//CUPPA:impl=-

CPPUNIT_TEST_SUITE_REGISTRATION(SourceLineTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(SourceLineTest,"zefiro_std");

}
