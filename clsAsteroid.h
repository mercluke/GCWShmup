#ifndef ASTEROID_H
#define ASTEROID_H
#include "globalConstants.h"

class clsAsteroid
{
public:
	clsAsteroid(void);
	~clsAsteroid(void);
	//virtual void setPicture(LPDIRECT3DDEVICE9 dev);
	void draw(SDL_Surface* screen);
	void move();
	void setXY(int x, int y);
	float getX();
	float getY();
	clsAsteroid* asteroidNext;
	bool checkDead();
	void takeDamage(bool damage/*, CSoundManager* SoundManager*/);
	int deathType;

protected:
	static const int HEIGHT = 32;
	static const int WIDTH =  32;
	float yPos;
	float xPos;
	//LPDIRECT3DTEXTURE9 sprite;
	float rotation;
	bool dead;
	int hp;
};
#endif