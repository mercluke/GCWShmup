#ifndef PLAYER_H
#define PLAYER_H
#include "globalConstants.h"

class clsPlayer
{
public:
	clsPlayer(void);
	~clsPlayer(void);
	void constructor();
	//void setPicture(LPDIRECT3DDEVICE9 dev);
	void draw(SDL_Surface* screen);
	void setXY(int x, int y);
	int getX();
	int getY();
	void move(int direction);
	int getHP();
	bool takeDamage(int);
	bool collide(float asteroidX, float asteroidY, int damage);

private:
	static const int NUMFRAMES = 3;
	static const int FRAMEWIDTH = 32;
	static const int FRAMEHEIGHT = 32;
	int frame;
	int frameXPos;
	//RECT part;
	float xPos;
	float yPos;
	//float rotate;
	//LPDIRECT3DTEXTURE9 sprite;
	int hp;
};
#endif