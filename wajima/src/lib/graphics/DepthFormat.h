/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/DepthFormat.h,v 1.5 2002/12/13 20:37:37 ama Exp $
 */
#ifndef __DEPTHFORMAT_H__
#define __DEPTHFORMAT_H__

namespace zefiro_graphics {
	class DepthFormat {
	public:
		enum FORMAT { D16_LOCKABLE , D32 , D15S1 , D24S8 , D16 , D24X8 , D24X4S4 , NONE };
		DepthFormat( FORMAT format ):format_(format){
		}
		FORMAT getFormat() const{
			return format_;
		}
		int getDepthBitLength() const{
			switch( format_ ){
			case D32:
				return 32;
			case D24S8:
			case D24X8:
			case D24X4S4:
				return 24;
			case D16_LOCKABLE:
			case D16:
				return 16;
			case D15S1:
				return 15;
			default:
				return 0;
			};
		}
		int getStencilBitLength() const{
			switch( format_ ){
			case D24S8:
				return 8;
			case D24X4S4:
				return 4;
			case D15S1:
				return 1;
			default:
				return 0;
			}
		}
		int getBitLength() const{
			switch( format_ ){
			case D32:
			case D24S8:
			case D24X8:
			case D24X4S4:
				return 32;
			case D16_LOCKABLE:
			case D16:
			case D15S1:
				return 16;
			default:
				return 0;
			}
		}
	private:
		FORMAT format_;
	};

	D3DFORMAT convertDepthFormatToD3DFORMAT( DepthFormat df ){
		switch( df.getFormat() ){
			case DepthFormat::D32:
				return D3DFMT_D32;
			case DepthFormat::D24S8:
				return D3DFMT_D24S8;
			case DepthFormat::D24X8:
				return D3DFMT_D24X8;
			case DepthFormat::D24X4S4:
				return D3DFMT_D24X4S4;
			case DepthFormat::D16_LOCKABLE:
				return D3DFMT_D16_LOCKABLE;
			case DepthFormat::D16:
				return D3DFMT_D16;
			case DepthFormat::D15S1:
				return D3DFMT_D15S1;
			default:
				return D3DFMT_UNKNOWN;
		}
	}
};


#endif //__DEPTHFORMAT_H__