/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/Attic/TextSpriteImp.h,v 1.4 2002/04/29 16:27:33 ama Exp $
 */

#ifndef __TEXTSPRITEIMP_H__
#define __TEXTSPRITEIMP_H__

#include "grahpics/BaseSpriteImp.h"

namespace zefiro_graphics {
	class TextSpriteImp : public BaseSpriteImp
	{
	public:
		TextSpriteImp( const string &text );
		TextSpriteImp( const TextSpriteImp &textSpriteImp );
		virtual ~TextSpriteImp();
		virtual void setText( const string &text );
		virtual string getText() const;
	protected:
		string	_text;
	};
};


#endif //__TEXTSPRITEIMP_H__