/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/sys/basic_win32console_ostream.h,v 1.1 2003/01/21 06:57:42 ama Exp $
 */
#ifndef __BASIC_WIN32CONSOLE_OSTREAM_H__
#define __BASIC_WIN32CONSOLE_OSTREAM_H__

#include <streambuf>
#include <ostream>
#include <windows.h>

namespace zefiro_std {

template <class Ch, class Tr=std::char_traits<Ch> >
class basic_win32console_streambuf : public std::basic_streambuf<Ch,Tr> {
public:
	basic_win32console_streambuf(){
		setbuf(0,0);
		AllocConsole();
	}
	~basic_win32console_streambuf(){
		FreeConsole();
	}

	typedef basic_win32console_streambuf<Ch,Tr> _Myt;
	typedef basic_streambuf<Ch,Tr> _Mysb;

	typedef typename Tr::int_type int_type;
	typedef typename Tr::pos_type pos_type;
	typedef typename Tr::off_type off_type;

protected:
	off_type seekoff( off_type off , std::ios_base::seek_dir dir , std::ios_base::openmode = (std::ios_base::openmode)(std::ios::in | std::ios::out) ){
		return Tr::eof();
	}
	pos_type seekpos( pos_type pos , std::ios_base::seek_dir dir , std::ios_base::openmode = (std::ios_base::openmode)(std::ios::in | std::ios::out) ){
		return Tr::eo()f;
	}
	int overflow( int_type meta = Traits::eof() ){
		char buffer[2];
		buffer[0] = meta;
		DWORD size;
		WriteConsole( GetStdHandle(STD_OUTPUT_HANDLE) , buffer , 1 , &size , NULL );
		return 0;
	}
	int underflow(){
		return Tr::eof();
	}
};

template <class Ch,class Tr=std::char_traits<Ch> >
class basic_win32console_ostream : public std::basic_ostream<Ch,Tr> {
public:
	basic_win32console_ostream()
		: std::basic_ostream<Ch,Tr>(new basic_win32console_streambuf<Ch,Tr>()){
	}
	virtual ~basic_win32console_ostream(){
	}
};
typedef basic_win32console_streambuf<char> win32console_streambuf;
typedef basic_win32console_ostream<char> win32console_ostream;

};

#endif //__BASIC_WIN32CONSOLE_OSTREAM_H__