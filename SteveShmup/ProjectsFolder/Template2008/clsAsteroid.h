#pragma once
#define HEIGHT 32
#define WIDTH  32
#include "globalConstants.h"

class clsAsteroid
{
public:
	clsAsteroid(void);
	~clsAsteroid(void);
	virtual void setPicture(LPDIRECT3DDEVICE9 dev);
	void draw(LPD3DXSPRITE spt);
	void move();
	void setXY(int x, int y);
	float getX();
	float getY();
	clsAsteroid* asteroidNext;
	bool checkDead();
	void takeDamage(bool damage, CSoundManager* SoundManager);
	int deathType;

protected:
	float yPos;
	float xPos;
	LPDIRECT3DTEXTURE9 sprite;
	float rotation;
	bool dead;
	int hp;
};
