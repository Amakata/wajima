#ifndef __D3DFONT__H__
#define __D3DFONT__H__

#include <windows.h>
#include <D3dx8core.h>

namespace zefiro_graphics {
	class D3DFont {
	public:
		D3DFont( LPD3DXFONT	d3dFont ): d3dFont_(d3dFont) {
		}
		virtual~D3DFont(){
			d3dFont_->Release();
		}
		void draw( std::string str , int x , int y , int width , int height , DWORD color ){
			RECT rect = { x , y , x + width , y + height };
			d3dFont_->DrawTextA( str.c_str() , -1, &rect, DT_WORD_ELLIPSIS, color );
		}
	protected:
		LPD3DXFONT d3dFont_;
	};
};

#endif // __D3DFONT__H__