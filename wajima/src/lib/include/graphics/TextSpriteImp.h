#ifndef __TEXTSPRITEIMP_H__
#define __TEXTSPRITEIMP_H__

#include <grahpics/BaseSpriteImp.h>

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