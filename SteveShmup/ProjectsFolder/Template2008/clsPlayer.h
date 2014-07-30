#pragma once
#define NUMFRAMES 3
#define FRAMEWIDTH 32
#define FRAMEHEIGHT 32
#include "globalConstants.h"

class clsPlayer
{
public:
	clsPlayer(void);
	~clsPlayer(void);
	void constructor();
	void setPicture(LPDIRECT3DDEVICE9 dev);
	void draw(LPD3DXSPRITE spt);
	void setXY(int x, int y);
	int getX();
	int getY();
	void move(int direction);
	int getHP();
	bool takeDamage(int);
	bool collide(float asteroidX, float asteroidY, int damage);

private:
	int frame;
	int frameXPos;
	RECT part;
	float xPos;
	float yPos;
	float rotate;
	LPDIRECT3DTEXTURE9 sprite;
	int hp;
};
