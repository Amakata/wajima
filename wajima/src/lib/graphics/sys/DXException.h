/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/DXException.h,v 1.3 2002/11/14 16:51:59 ama Exp $
 */
#ifndef __DXEXCEPTION_H__
#define __DXEXCEPTION_H__

#include <d3d8.h>

#include "std/Exception.h"

namespace zefiro_graphics {
	class DXException : virtual public zefiro_std::Exception
	{
	public:
		DXException( std::string message , HRESULT hr , zefiro_std::SourceLine sourceLine = zefiro_std::SourceLine());
		DXException( std::string message , HRESULT hr , long lineNumber, std::string fileName );
		DXException( const DXException &other );
		virtual ~DXException() throw();
		HRESULT getHResult() const;
		/** Copy operator.
		* @param other Object to copy.
		* @return Reference on this object.
		*/
		DXException &operator =( const DXException &other );
		zefiro_std::Exception *clone() const;
		bool isInstanceOf( const Type &type ) const;
		static Type type();
	protected:
		HRESULT	_hr;
	};
};

#endif //__DXEXCEPTION_H__