#include <typeinfo.h>

#include <graphics/test/SpriteFactoryTest.h>
#include <graphics/SpriteFactory.h>
#include <graphics/sys/Win32SpriteFactory.h>

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_graphicstest::SpriteFactoryTest );

namespace zefiro_graphicstest{
	void SpriteFactoryTest::setUp(){
		_spriteFactory = zefiro_graphics::SpriteFactory::createSpriteFactory();
	}
	void SpriteFactoryTest::tearDown(){
		delete _spriteFactory;
	}
	void SpriteFactoryTest::testCreateSpriteFactory(){
		CPPUNIT_ASSERT_EQUAL( std::string(typeid(*_spriteFactory).name()) , std::string("class zefiro_graphics::Win32SpriteFactory") );
	}
};