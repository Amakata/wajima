/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/DXInvalidArgument.h,v 1.3 2002/11/12 15:47:44 ama Exp $
 */
#ifndef __DXINVALIDARGUMENT_H__
#define __DXINVALIDARGUMENT_H__

#include "std/InvalidArgument.h"

#include "DXException.h"


namespace zefiro_graphics {
	class DXInvalidArgument : public DXException , public zefiro_std::InvalidArgument
	{
	public:
		DXInvalidArgument( HRESULT hr , zefiro_std::SourceLine sourceLine = zefiro_std::SourceLine() , std::string additionalMessage = "" );
		DXInvalidArgument( HRESULT hr , long lineNumber, 
                     std::string fileName ,std::string additionalMessage = "");
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