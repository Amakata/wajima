/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/ColorFormat.h,v 1.1 2002/11/24 14:53:45 ama Exp $
 */
#ifndef __COLORFORMAT_H__
#define __COLORFORMAT_H__

namespace zefiro_graphics {
	class ColorFormat {
	public:
		enum FORMAT { RGB888 , ARGB8888 , XRGB8888 , RGB565 , XRGB1555 , ARGB1555 };
		ColorFormat( FORMAT format ):format_(format){
		}
		FORMAT getFormat() const{
			return format_;
		}
		int getRGBBitLength() const{
			switch( format_ ){
				case RGB888:
				case ARGB8888:
				case XRGB8888:
					return 24;
				case RGB565:
					return 16;
				case XRGB1555:
				case ARGB1555:
					return 15;
				default:
					return 0;
			}
		}
		int getABitLength() const{
			switch( format_ ){
				case ARGB8888:
					return 8;
				case ARGB1555:
					return 1;
				default:
					return 0;
			}
		}
		int getBitLength() const{
			switch( format_ ){
				case ARGB8888:
				case XRGB8888:
					return 32;
				case RGB888:
					return 24;
				case RGB565:
				case XRGB1555:
				case ARGB1555:
					return 16;
			}
		}
	protected:
		FORMAT format_;
	};
};

#endif //__COLORFORMAT_H__