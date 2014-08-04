#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include "globalConstants.h"
class clsHealthBar
{
public:
	clsHealthBar(void);
	~clsHealthBar(void);
//	void setPicture(LPDIRECT3DDEVICE9 dev);
	void draw(SDL_Surface* screen, int hp);

private:
//	RECT part;
//	LPDIRECT3DTEXTURE9 sprite;
//	LPDIRECT3DTEXTURE9 spriteEdge;
};
#endif