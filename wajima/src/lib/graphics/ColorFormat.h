/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/ColorFormat.h,v 1.4 2002/12/13 20:37:37 ama Exp $
 */
#ifndef __COLORFORMAT_H__
#define __COLORFORMAT_H__

namespace zefiro_graphics {
	class ColorFormat {
	public:
		enum FORMAT { R8G8B8 , A8R8G8B8 , X8R8G8B8 , R5G6B5 , X1R5G5B5 , A1R5G5B5 , NONE };
		ColorFormat( FORMAT format ):format_(format){
		}
		FORMAT getFormat() const{
			return format_;
		}
		int getRGBBitLength() const{
			switch( format_ ){
				case R8G8B8:
				case A8R8G8B8:
				case X8R8G8B8:
					return 24;
				case R5G6B5:
					return 16;
				case X1R5G5B5:
				case A1R5G5B5:
					return 15;
				default:
					return 0;
			}
		}
		int getABitLength() const{
			switch( format_ ){
				case A8R8G8B8:
					return 8;
				case A1R5G5B5:
					return 1;
				default:
					return 0;
			}
		}
		int getBitLength() const{
			switch( format_ ){
				case A8R8G8B8:
				case X8R8G8B8:
					return 32;
				case R8G8B8:
					return 24;
				case R5G6B5:
				case X1R5G5B5:
				case A1R5G5B5:
					return 16;
				default:
					return 0;
			}
		}
	protected:
		FORMAT format_;
	};
	D3DFORMAT convertColorFormatToD3DFORMAT( ColorFormat cf ){
		switch( cf.getFormat() ){
			case ColorFormat::A8R8G8B8:
				return D3DFMT_A8R8G8B8;
			case ColorFormat::X8R8G8B8:
				return D3DFMT_X8R8G8B8;
			case ColorFormat::R8G8B8:
				return D3DFMT_R8G8B8;
			case ColorFormat::R5G6B5:
				return D3DFMT_R5G6B5;
			case ColorFormat::X1R5G5B5:
				return D3DFMT_X1R5G5B5;
			case ColorFormat::A1R5G5B5:
				return D3DFMT_A1R5G5B5;
			default:
				return (D3DFORMAT)0;
		}
	};
};

#endif //__COLORFORMAT_H__