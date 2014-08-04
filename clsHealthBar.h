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
	SDL_Rect part;
	SDL_Rect posEdge;
	SDL_Surface* sprite;
	SDL_Surface* sprEdge;
	static const int HEIGHT = 16;
	static const int WIDTH = 160;
	static const int EDGEWIDTH = 16;
};
#endif