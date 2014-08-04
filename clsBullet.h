#ifndef BULLET_H
#define BULLET_H
#define HEIGHT 
#include "globalConstants.h"

class clsBullet
{
public:
	clsBullet(void);
	~clsBullet(void);
	clsBullet* bulletNext;
	//void setPicture(LPDIRECT3DDEVICE9 dev);
	//void draw(LPD3DXSPRITE spt);
	void setXY(int x, int y);
	int getX();
	int getY();
	void move(int direction);
	bool checkDead();
	bool collide(float asteroidX, float asteroidY);

private:
	float xPos;
	float yPos;
	//LPDIRECT3DTEXTURE9 sprite;
	bool dead;
};
#endif