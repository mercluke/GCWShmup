#pragma once
#include "globalConstants.h"
class clsHealthBar
{
public:
	clsHealthBar(void);
	~clsHealthBar(void);
	void setPicture(LPDIRECT3DDEVICE9 dev);
	void draw(LPD3DXSPRITE spt, int hp);

private:
	RECT part;
	LPDIRECT3DTEXTURE9 sprite;
	LPDIRECT3DTEXTURE9 spriteEdge;
};
