/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/test/Attic/UniqueNumberFactoryTest.cpp,v 1.4 2002/04/28 13:31:47 ama Exp $
 */

#include <limits>
#include <std/test/UniqueNumberFactoryTest.h>
#include <std/UniqueNumberBadAlloc.h>

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_stdtest::UniqueNumberFactoryTest );

namespace zefiro_stdtest{
	void UniqueNumberFactoryTest::setUp(){
		_uniqueNumberFactory = new zefiro_std::UniqueNumberFactory();
		_uniqueNumberFactoryUpperBound = new zefiro_std::UniqueNumberFactory(std::numeric_limits<int>::max()-1);
	}
	void UniqueNumberFactoryTest::tearDown(){
		delete _uniqueNumberFactoryUpperBound;
		delete _uniqueNumberFactory;
	}
	void UniqueNumberFactoryTest::testRepeat(){
		for( int count=0 ; count<10 ; ++count ){
			CPPUNIT_ASSERT( count + 1 == _uniqueNumberFactory->createNumber() );
		}
	}
	void UniqueNumberFactoryTest::testDelete(){
		int uniqueNumber = _uniqueNumberFactory->createNumber();
		_uniqueNumberFactory->deleteNumber( uniqueNumber );
		CPPUNIT_ASSERT( _uniqueNumberFactory->createNumber() == uniqueNumber );
	}
	void UniqueNumberFactoryTest::testUpperBound(){
		CPPUNIT_ASSERT( _uniqueNumberFactoryUpperBound->createNumber() == std::numeric_limits<int>::max() );
		_uniqueNumberFactoryUpperBound->createNumber();
	}
};