/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/DepthFormat.h,v 1.2 2002/12/13 18:25:13 ama Exp $
 */
#ifndef __DEPTHFORMAT_H__
#define __DEPTHFORMAT_H__

namespace zefiro_graphics {
	class DepthFormat {
	public:
		enum FORMAT { D16_LOCKABLE , D32 , D15S1 , D24S8 , D16 , D24X8 , D24X4S4 };
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
			case D16S1:
				return 16;
			default:
				return 0;
			}
		}
	private:
		FORMAT format_;
	};
};


#endif //__DEPTHFORMAT_H__