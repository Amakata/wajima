/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/std/test/Attic/UniqueNumberFactoryTest.h,v 1.2 2002/05/23 15:59:35 ama Exp $
 */

#ifndef __UNIQUENUMBERFACTORYTEST_H__
#define __UNIQUENUMBERFACTORYTEST_H__

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include "std/UniqueNumberFactory.h"

namespace zefiro_stdtest{
	class UniqueNumberFactoryTest : public CppUnit::TestCase
	{
		CPPUNIT_TEST_SUITE( UniqueNumberFactoryTest );
		CPPUNIT_TEST( testRepeat );
		CPPUNIT_TEST( testDelete );
		CPPUNIT_TEST_EXCEPTION( testUpperBound , zefiro_std::UniqueNumberBadAlloc );
		CPPUNIT_TEST_SUITE_END();
	protected:
		zefiro_std::UniqueNumberFactory	*_uniqueNumberFactory;
		zefiro_std::UniqueNumberFactory *_uniqueNumberFactoryUpperBound;
	public:
		void setUp();
		void tearDown();
		///	ユニークナンバーの繰り返し生成テスト
		void testRepeat();
		///	ユニークナンバーの削除と生成のテスト
		void testDelete();
		///	ユニークナンバーの境界値テスト
		void testUpperBound();
	};
};

#endif //__UNIQUENUMBERFACTORYTEST_H__