/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/test/lib/ApplicationTest.h,v 1.3 2002/11/13 18:23:21 ama Exp $
 */

#ifndef __APPLICATIONTEST_H__
#define __APPLICATIONTEST_H__

#include <windows.h>
#include <fstream>
#include <string>

extern HWND hWnd__;

class ApplicationTest
{
public:
	ApplicationTest( HWND hWnd );
	virtual ~ApplicationTest();
	void testUnit();
	void testThread();
	void testThreadNotify();
protected:
	void exec( std::string cmdLine );
	std::ofstream ostr_;
 	HWND hWnd_;
};




#endif //__APPLICATIONTEST_H__