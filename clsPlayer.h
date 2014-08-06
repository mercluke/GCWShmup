#ifndef PLAYER_H
#define PLAYER_H
#include "globalStuff.h"

class clsPlayer
{
public:
	clsPlayer(void);
	~clsPlayer(void);
	void draw(SDL_Surface* screen);
	void setXY(int x, int y);
	int getX();
	int getY();
	void move(int direction);
	int getHP();
	void upHP(int bonus);
	void reset(void);
	bool takeDamage(int);
	bool collide(float asteroidX, float asteroidY, int damage);

private:
	static const int NUMFRAMES = 3;
	static const int FRAMEWIDTH = 16;
	static const int FRAMEHEIGHT = 16;
	static const float SPEEDMODIFIER = 0.5;
	int frame;
	SDL_Rect view;
	float xPos;
	float yPos;
	SDL_Rect pos;
	SDL_Surface* sprite;
	int hp;
};
#endif