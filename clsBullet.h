#ifndef BULLET_H
#define BULLET_H
#include "globalConstants.h"

class clsBullet
{
public:
	clsBullet(void);
	~clsBullet(void);
	clsBullet* bulletNext;
	//void setPicture(LPDIRECT3DDEVICE9 dev);
	void draw(SDL_Surface* screen);
	void setXY(int x, int y);
	int getX();
	int getY();
	void move(int direction);
	bool checkDead();
	void freeList();
	bool collide(float asteroidX, float asteroidY);

private:
	float xPos;
	float yPos;
	SDL_Rect pos;
	static SDL_Surface* sprite;
	bool dead;
	static const int BULLET_HEIGHT = 6;
	static const int FRAME_HEIGHT = 16;
};
#endif