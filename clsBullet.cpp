#include "clsBullet.h"

SDL_Surface* clsBullet::sprite = NULL;

clsBullet::clsBullet(void)
{
	bulletNext=NULL;
	dead = false;

	//only load the bitmap once rather than for each bullet
	if(sprite == NULL)
	{
		sprite = SDL_LoadBMP("data/bullet.bmp");
		//hot pink is transparent
    	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 255));
	}
}

clsBullet::~clsBullet(void)
{
}


//recursively kill entire list
void clsBullet::freeList()
{
	if(sprite != NULL)
	{
		SDL_FreeSurface(sprite);
		sprite = NULL;
	}
	if(bulletNext != NULL)
	{
		bulletNext->freeList();
	}
	delete this;
}

//draw bullet to screen
void clsBullet::draw(SDL_Surface* screen)
{
    pos.x = xPos;
    pos.y = yPos;
    SDL_BlitSurface(sprite, NULL, screen, &pos);
}

//change position of bullet (make it spawn in front of player)
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

//move bullet
void clsBullet::move(int direction)
{
	if(direction == DIR_UP)//up
	{
		//move up
		if(yPos > 0)
		{
			yPos-=(SPEED*3);

		}
		//bullet went offscreen
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

//check collision with asteroid
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