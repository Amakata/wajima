/**
 * $Header : $
 */
#ifndef __DXEXCEPTION_H__
#define __DXEXCEPTION_H__

#include <d3d8.h>

#include "std/Exception.h"

namespace zefiro_graphics {
	class DXException : virtual public zefiro_std::Exception
	{
	public:
		DXException( HRESULT hr , zefiro_std::SourceLine sourceLine = zefiro_std::SourceLine(),
                     std::string additionalMessage = "" );
		DXException( HRESULT hr , long lineNumber, 
                     std::string fileName ,std::string additionalMessage = "");
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