#ifndef __SPRITEFACTORYTEST_H__
#define __SPRITEFACTORYTEST_H__

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include <graphics/SpriteFactory.h>

namespace zefiro_graphicstest{
	class SpriteFactoryTest : public CppUnit::TestCase {
		CPPUNIT_TEST_SUITE( SpriteFactoryTest );
		CPPUNIT_TEST( testCreateSpriteFactory );
		CPPUNIT_TEST_SUITE_END();
	public:
		void setUp();
		void tearDown();
		void testCreateSpriteFactory();
	protected:
		zefiro_graphics::SpriteFactory *_spriteFactory;
	};
};

#endif //__SPRITEFACTORYTEST_H__