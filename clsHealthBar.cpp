#include "clsHealthBar.h"

clsHealthBar::clsHealthBar(void)
{
    //load bitmaps
    sprite = SDL_LoadBMP("data/health.bmp");
    sprEdge = SDL_LoadBMP("data/healthEdge.bmp");
    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 255));
    SDL_SetColorKey(sprEdge, SDL_SRCCOLORKEY, SDL_MapRGB(sprEdge->format, 255, 0, 255));
    posEdge.h = HEIGHT;
    posEdge.w = EDGEWIDTH;
    posEdge.y = 0;
    view.x = 0;
    view.y = 0;
    view.h = HEIGHT;
    view.w = WIDTH;
}

clsHealthBar::~clsHealthBar(void)
{
	SDL_FreeSurface(sprite);
}

//draw bar onscreen
void clsHealthBar::draw(SDL_Surface* screen, int hp)
{
    posEdge.x = view.w;
    view.w = (WIDTH / FULLHEALTH)*hp;

    if(hp)
    {
        SDL_BlitSurface(sprEdge, NULL, screen, &posEdge);
    }
    
    SDL_BlitSurface(sprite, &view, screen, NULL);
	
}