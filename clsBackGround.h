#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "globalConstants.h"

class clsBackGround
{
public:
	clsBackGround(void);
	~clsBackGround(void);
	void constructor();
	//void setPicture(LPDIRECT3DDEVICE9 dev);
	void draw(SDL_Surface* screen);
	void move();

private:
	SDL_Surface* sprite;
	SDL_Rect bg1pos;
	SDL_Rect bg2pos;
	SDL_Rect bg2view;
	static const int HEIGHT = 320;
};
#endif