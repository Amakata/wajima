/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/Color.h,v 1.1 2002/12/15 10:38:25 ama Exp $
 */
#ifndef __COLOR_H__
#define __COLOR_H__

#include <windows.h>

namespace zefiro_graphics {

	class Color {
	public:
		Color(){
			color_[3] = 0xff;
			color_[2] = 0;
			color_[1] = 0;
			color_[0] = 0;
		}
		Color( BYTE r , BYTE g , BYTE b , BYTE a = 0xff ){
			color_[3] = a;
			color_[2] = r;
			color_[1] = g;
			color_[0] = b;
		}
		BYTE getR() const {
			return color_[2];
		}
		BYTE getG() const {
			return color_[1];
		}
		BYTE getB() const {
			return color_[0];
		}
		BYTE getA() const {
			return color_[3];
		}
		DWORD getColor() const {
			return *((DWORD*)color_);
		}
	private:
		BYTE color_[4];	//	a r g b
	};
};

#endif //__COLOR_H__