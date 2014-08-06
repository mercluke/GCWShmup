//#include "StdAfx.h"
#include "clsBullet.h"

SDL_Surface* clsBullet::sprite = NULL;

clsBullet::clsBullet(void)
{
	bulletNext=NULL;
	dead = false;

	if(sprite == NULL)
	{
		sprite = SDL_LoadBMP("data/bullet.bmp");
    	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 255));
	}
}

clsBullet::~clsBullet(void)
{
}


void clsBullet::freeList()
{
	if(bulletNext != NULL)
	{
		bulletNext->freeList();
		delete this;
	}
	if(sprite != NULL)
	{
		SDL_FreeSurface(sprite);
		sprite = NULL;
	}
}


void clsBullet::draw(SDL_Surface* screen)
{
    pos.x = xPos;
    pos.y = yPos;
    SDL_BlitSurface(sprite, NULL, screen, &pos);
}

void clsBullet::setXY(int x, int y)
{
	xPos = x;
	yPos = y;

}

int clsBullet::getX()
{
	return xPos;

}

int clsBullet::getY()
{
	return yPos;

}

void clsBullet::move(int direction)
{
	if(direction == DIR_UP)//up
	{
		if(yPos > 0)
		{
			yPos-=(SPEED*3);

		}
		else 
		{
			yPos = 0;
			dead = true;
		}
	}
}

bool clsBullet::checkDead()
{
	return dead;
}

bool clsBullet::collide(float AsteroidX, float AsteroidY)
{
	if((xPos+FRAME_HEIGHT) > AsteroidX && xPos < (AsteroidX+FRAME_HEIGHT))
	{
		if((yPos+BULLET_HEIGHT) < (AsteroidY + FRAME_HEIGHT) && (yPos+BULLET_HEIGHT) > AsteroidY)
		{
			dead = true;
			return true;
		}
	}
	return false;
}