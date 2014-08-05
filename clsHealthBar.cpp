//#include "StdAfx.h"
#include "clsHealthBar.h"

clsHealthBar::clsHealthBar(void)
{
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

/*void clsHealthBar::setPicture(LPDIRECT3DDEVICE9 dev)
{
	D3DXCreateTextureFromFileEx(dev, L"data/health.png",    // the file name
                                D3DX_DEFAULT,    // default width
                                D3DX_DEFAULT,    // default height
                                D3DX_DEFAULT,    // no mip mapping
                                NULL,    // regular usage
                                D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
                                D3DPOOL_MANAGED,    // typical memory handling
                                D3DX_DEFAULT,    // no filtering
                                D3DX_DEFAULT,    // no mip filtering
                                D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
                                NULL,    // no image info struct
                                NULL,    // not using 256 colors
                                &sprite);    // load to sprite
	D3DXCreateTextureFromFileEx(dev, L"data/healthEdge.png",    // the file name
                                D3DX_DEFAULT,    // default width
                                D3DX_DEFAULT,    // default height
                                D3DX_DEFAULT,    // no mip mapping
                                NULL,    // regular usage
                                D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
                                D3DPOOL_MANAGED,    // typical memory handling
                                D3DX_DEFAULT,    // no filtering
                                D3DX_DEFAULT,    // no mip filtering
                                D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
                                NULL,    // no image info struct
                                NULL,    // not using 256 colors
                                &spriteEdge);    // load to sprite
}*/

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