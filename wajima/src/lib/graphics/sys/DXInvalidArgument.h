/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/DXInvalidArgument.h,v 1.4 2002/11/14 16:51:59 ama Exp $
 */
#ifndef __DXINVALIDARGUMENT_H__
#define __DXINVALIDARGUMENT_H__

#include "std/InvalidArgument.h"

#include "DXException.h"


namespace zefiro_graphics {
	class DXInvalidArgument : public DXException , public zefiro_std::InvalidArgument
	{
	public:
		DXInvalidArgument( std::string message , HRESULT hr , zefiro_std::SourceLine sourceLine = zefiro_std::SourceLine()  );
		DXInvalidArgument( std::string message , HRESULT hr , long lineNumber, std::string fileName );
		DXInvalidArgument( const DXInvalidArgument &other );
		virtual ~DXInvalidArgument() throw();
		/** Copy operator.
		* @param other Object to copy.
		* @return Reference on this object.
		*/
		DXInvalidArgument &operator =( const DXInvalidArgument &other );
		zefiro_std::Exception *clone() const;
		bool isInstanceOf( const Type &type ) const;
		static Type type();
	};
};

#endif //__DXINVALIDARGUMENT_H__