#include "clsPlayer.h"

clsPlayer::clsPlayer(void)
{
	//load bitmap for player's plane
	sprite = SDL_LoadBMP("data/plane.bmp");
    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 0, 255));
    reset();
}

//unload bitmap
clsPlayer::~clsPlayer(void)
{
	SDL_FreeSurface(sprite);
}

//intial values
void clsPlayer::reset(void)
{
	frame = 0;
	xPos = pos.x = (SCREEN_WIDTH-FRAMEWIDTH)/2;
	yPos = pos.y = SCREEN_HEIGHT-FRAMEHEIGHT;
	view.x = 0; view.y = 0;
	view.h = pos.h = FRAMEHEIGHT;
	view.w =  pos.w = FRAMEWIDTH;
	hp = FULLHEALTH;
}

//display player onscreen
void clsPlayer::draw(SDL_Surface* screen)
{

	//animate player
    if(frame == NUMFRAMES) 
    	{frame=0;}
    else if(frame < NUMFRAMES) 
    	{frame++;}     // if we aren't on the last frame, go to the next frame
	
	pos.x = xPos;
	pos.y = yPos;
	view.x = FRAMEWIDTH*frame;

	SDL_BlitSurface(sprite, &view, screen, &pos);

}

void clsPlayer::setXY(int x, int y)
{
	xPos = x;
	yPos = y;

}

int clsPlayer::getX()
{
	return xPos;

}

int clsPlayer::getY()
{
	return yPos;

}

//move player
void clsPlayer::move(int direction)
{
	if(direction == DIR_UP && yPos > 0)//up
	{
		if(yPos < (SPEED/1.5))
		{
			yPos = 0;
		}
		else
		{
			yPos-=(SPEED/1.5);
		}
	}
	else if(direction == DIR_DOWN && yPos < (SCREEN_HEIGHT-FRAMEHEIGHT))//down
	{
		if(yPos > ((SCREEN_HEIGHT-FRAMEHEIGHT)-SPEED))
		{
			yPos=(SCREEN_HEIGHT-FRAMEHEIGHT);
		}
		else
		{
			yPos+=SPEED;
		}
	}
	else if(direction == DIR_LEFT && xPos > 0)//left
	{
		if(xPos < SPEED)
		{
			xPos = 0;
		}
		else
		{
			//closer you are to the top of the screen, the faster you strafe
			xPos-=(SPEED + (SPEEDMODIFIER - ((SPEEDMODIFIER / (SCREEN_HEIGHT-FRAMEHEIGHT))*yPos)));
		}
	}
	else if(direction == DIR_RIGHT && xPos < (SCREEN_WIDTH-(FRAMEWIDTH)))//right
	{
		if(xPos > ((SCREEN_WIDTH-(FRAMEWIDTH))-SPEED))
		{
			xPos = (SCREEN_WIDTH-(FRAMEWIDTH));
		}
		else
		{
			//closer you are to the top of the screen, the faster you strafe
			xPos+=(SPEED + (SPEEDMODIFIER - ((SPEEDMODIFIER / (SCREEN_HEIGHT-FRAMEHEIGHT))*yPos)));
		}
	}
	else if(direction == DIR_DRIFT && yPos < (SCREEN_HEIGHT-FRAMEHEIGHT))//downward drift
	{
		if(yPos > ((SCREEN_HEIGHT-FRAMEHEIGHT)-(float)(SPEED/4)))
		{
			yPos=(SCREEN_HEIGHT-FRAMEHEIGHT);
		}
		else
		{
			yPos+=(float)(SPEED/4);
		}
	}
}

//player damaged
bool clsPlayer::takeDamage(int damage)
{
	if(hp > damage)
	{
		hp -= damage;
		return false;
	}
	else
	{
		hp=0;
		return true;
	}
}

//player crashed
bool clsPlayer::collide(float AsteroidX, float AsteroidY, int damage)
{
	if((xPos+FRAMEWIDTH) > AsteroidX && xPos < (AsteroidX+FRAMEWIDTH))
	{
		if(yPos < (AsteroidY + FRAMEHEIGHT) && (yPos+FRAMEHEIGHT) > AsteroidY)
		{
			hp -= damage;
			return true;
		}
	}
	return false;
}


int clsPlayer::getHP()
{
	return hp;
}

//health pack
void clsPlayer::upHP(int bonus)
{
	//cap hp at "FULLHEALTH"
	hp = (bonus+hp <= FULLHEALTH) ? bonus+hp : FULLHEALTH;
}