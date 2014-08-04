#ifndef BACKGROUND_H
#define BACKGROUND_H
#define HEIGHT 320
#include "globalConstants.h"

class clsBackGround
{
public:
	clsBackGround(void);
	~clsBackGround(void);
	void constructor();
	//void setPicture(LPDIRECT3DDEVICE9 dev);
	//void draw(LPD3DXSPRITE spt);
	void move();

private:
	float yPos;
	float yPos2;
	//LPDIRECT3DTEXTURE9 sprite;
};
#endif