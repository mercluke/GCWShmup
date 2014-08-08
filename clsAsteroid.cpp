#include "clsAsteroid.h"

SDL_Surface* clsAsteroid::sprite = NULL;

clsAsteroid::clsAsteroid(void)
{
	//load bitmap if not already loaded
	if(sprite == NULL)
	{
		sprite = SDL_LoadBMP("data/asteroid1.bmp");
    	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 255));
	}
	yPos = (0-SCREEN_HEIGHT);
	xPos = (rand()%(SCREEN_WIDTH-WIDTH)); //starts at a random horizontal position to make games a little less boring
	asteroidNext=NULL;
	dead = false;
	//som random amount of hp between 1-5
	hp = (rand()%5)+1;
}

clsAsteroid::~clsAsteroid(void)
{
	
}

//recursively kill entire list
void clsAsteroid::freeList()
{
	if(sprite != NULL)
	{
		SDL_FreeSurface(sprite);
		sprite = NULL;
	}
	
	if(asteroidNext != NULL)
	{
		asteroidNext->freeList();
	}
	delete this;
}

void clsAsteroid::setXY(int x, int y) //not used atm but w/e
{
	xPos = x;
	yPos = y;
}

float clsAsteroid::getX() 
{
	return xPos;
}

float clsAsteroid::getY() 
{
	return yPos;
}

//draw sateroid to screen
void clsAsteroid::draw(SDL_Surface* screen)
{
    pos.x = xPos;
    pos.y = yPos;
    SDL_BlitSurface(sprite, NULL, screen, &pos);
}

//move asteroid down
void clsAsteroid::move()
{
	if(yPos < (SCREEN_HEIGHT-1))
	{
		yPos += (SPEED/3);
	}
	else
	{
		dead = true;
		deathType = 1; //fall offscreen
	}
}

bool clsAsteroid::checkDead()
{
	return dead;
}

void clsAsteroid::takeDamage(bool damage)
{
	if(damage)
	{
		if(hp > 1)
		{
			hp--;
		}
		else
		{
			dead = true;
			deathType = 2; //get shot
		}
	}
}

