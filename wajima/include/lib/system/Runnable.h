/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/system/Attic/Runnable.h,v 1.3 2002/05/25 15:58:21 ama Exp $
 */

#ifndef __RUNNABLE_H__
#define __RUNNABLE_H__

namespace zefiro_system {
	class Runnable
	{
	public:
		virtual void run()=0;
	};
};
#endif //__RUNNABLE_H__