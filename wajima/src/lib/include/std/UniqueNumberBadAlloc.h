#ifndef __UNIQUENUMBERBADALLOC_H__
#define __UNIQUENUMBERBADALLOC_H__

#include <std/Exception.h>
#include <string>

namespace zefiro_std {
	/**
	 * ���j�[�N�i���o�[�̊��蓖�ăG���[
	 * ���j�[�N�i���o�[�̊��蓖�Ď������g������A���蓖�Ă��Ȃ��Ƃ��ɔ�������B
	 */
	class UniqueNumberBadAlloc : public zefiro_std::Exception
	{
	public:

		UniqueNumberBadAlloc( std::string message="A unique number is not assigned." , long lineNumber =  UNKNOWNLINENUMBER , std::string fileName = UNKNOWNFILENAME );
		virtual Exception *clone() const;
		UniqueNumberBadAlloc & operator= (const UniqueNumberBadAlloc& other );
		virtual bool isInstanceOf( const Exception::Type &type ) const;
		static Exception::Type getType();		
	};
};

#endif //__UNIQUENUMBERBADALLOC_H__