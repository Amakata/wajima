/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/DepthFormat.h,v 1.1 2002/11/26 11:31:35 ama Exp $
 */
	#ifndef __DEPTHFORMAT_H__
#define __DEPTHFORMAT_H__

namespace zefiro_graphics {
	class DepthFormat {
	public:
		enum FORMAT { D16LOCK , D32 , D15S1 , D24S8 , D16 , D24X8 , D24X4S4 };
		DepthFormat( FORMAT f ):format_(f){
		}
		int getBitLength() const {
			switch( format_ ){
				case D32:
					return 32;
				case D24S8:
				case D24X8:
				case D24X4S4:
					return 24;
				case D16LOCK:
				case D16:
					return 16;
				case D15S1:
					return 15;
				default:
					return 0;
			}
		}
		FORMAT getFormat() const {
			return format_;
		}
	private:
		FORMAT format_;
	};
};

#endif //__DEPTHFORMAT_H__