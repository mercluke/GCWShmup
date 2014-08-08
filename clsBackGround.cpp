#include "clsBackGround.h"

clsBackGround::clsBackGround(void)
{
	//load backround image
	sprite = SDL_LoadBMP("data/back_4-3.bmp");

	bg1pos.x = bg1pos.y = bg2pos.x = bg2view.x = bg2view.h = 0;
	bg2view.w = SCREEN_WIDTH;
	bg2view.y = SCREEN_HEIGHT;

}

clsBackGround::~clsBackGround(void)
{
	SDL_FreeSurface(sprite);
}

void clsBackGround::draw(SDL_Surface* screen)
{
	//draw top and bottom section of bg
	SDL_BlitSurface(sprite, NULL, screen, &bg1pos);
	SDL_BlitSurface(sprite, &bg2view, screen, &bg2pos);
}

void clsBackGround::move()
{
	//scroll the background
	if(bg1pos.y >= SCREEN_HEIGHT)
	{
		bg1pos.y = 0;
		bg2view.y = SCREEN_HEIGHT;
		bg2view.h = 0;
	}
	else
	{
		bg2view.y -= SPEED;
		bg2view.h += SPEED;
		bg1pos.y += SPEED;
	}
}