/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsDeviceMode.h,v 1.1 2002/11/24 14:53:59 ama Exp $
 */
#ifndef __GRAPHICSDEVICEMODE_H__
#define __GRAPHICSDEVICEMODE_H__

#include "ColorFormat.h"

namespace zefiro_graphics {
	class GraphicsDeviceMode {
	public:
		GraphicsDeviceMode( int width , int height , ColorFormat colorFormat , int refreshRate , bool windowed )
			: width_(width),height_(height),colorFormat_(colorFormat),refreshRate_(refreshRate),windowed_(windowed){
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
	private:
		int width_;
		int height_;
		ColorFormat colorFormat_;
		int refreshRate_;
		bool windowed_;
	};
};

#endif //__GRAPHICSDEVICEMODE_H__