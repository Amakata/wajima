#ifndef __D3DDEVICE8_H__
#define __D3DDEVICE8_H__

namespace zefiro_graphics {
	class D3DDevice8{
	public:
		D3DDevice8();
		virtual ~D3DDevice8();

	protected:
		LPDIRECT3DDEVICE8	_pD3DDevice8;
	};
};

#endif //__D3DDEVICE8_H__