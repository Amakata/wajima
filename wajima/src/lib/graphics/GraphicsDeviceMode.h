/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsDeviceMode.h,v 1.2 2002/11/24 17:42:20 ama Exp $
 */
#ifndef __GRAPHICSDEVICEMODE_H__
#define __GRAPHICSDEVICEMODE_H__

#include "ColorFormat.h"

namespace zefiro_graphics {
	class GraphicsDeviceMode {
	public:
		GraphicsDeviceMode( int width , int height , ColorFormat colorFormat , int refreshRate , bool windowed , int adapterNumber )
			: width_(width),height_(height),colorFormat_(colorFormat),refreshRate_(refreshRate),windowed_(windowed),adapterNumber_(adapterNumber){
		}
		int getWidth() const {
			return width_;
		}
		int getHeight() const {
			return height_;
		}
		ColorFormat getColorFormat() const{
			return colorFormat_;
		}
		int getRefreshRate() const{
			return refreshRate_;
		}
		bool getWindowed() const{
			return windowed_;
		}
		int getAdapterNumber() const{
			return adapterNumber_;
		}
	private:
		int width_;
		int height_;
		ColorFormat colorFormat_;
		int refreshRate_;
		bool windowed_;
		int adapterNumber_;
	};
};

#endif //__GRAPHICSDEVICEMODE_H__