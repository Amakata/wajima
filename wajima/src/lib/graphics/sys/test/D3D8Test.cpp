#include <graphics/sys/test/D3D8Test.h>

namespace zefiro_graphicstest{
	void D3D8Test::setUp(){
		_d3d8 = new zefiro_graphics::D3D8();
	}
	void D3D8Test::tearDown(){
		delete _d3d8;
	}
	void D3D8Test::test(){
	}
};