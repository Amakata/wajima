#pragma once

#include <d3d8.h>

#define D3DFVF_CUSTOMVERTEX	( D3DFVF_XYZRHW|D3DFVF_TEX1)

typedef struct CUSTOMVERTEX_ {
	float x,y,z,rhw;
	float tu,tv;
}CUSTOMVERTEX;

