#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include "globalConstants.h"
class clsHealthBar
{
public:
	clsHealthBar(void);
	~clsHealthBar(void);
	void draw(SDL_Surface* screen, int hp);

private:
	SDL_Rect view;
	SDL_Rect posEdge;
	SDL_Surface* sprite;
	SDL_Surface* sprEdge;
	static const int HEIGHT = 8;
	static const int WIDTH = 80;
	static const int EDGEWIDTH = 16;
};
#endif