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