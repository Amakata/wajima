#ifndef __RUNNABLE_H__
#define __RUNNABLE_H__
/**
 * $ Header: $
 */
namespace zefiro_thread {
	class Runnable
	{
	public:
		virtual void run()=0;
	};
};
#endif //__RUNNABLE_H__