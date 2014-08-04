#include "clsPlayer.h"

clsPlayer::clsPlayer(void)
{
	constructor();
}

clsPlayer::~clsPlayer(void)
{
	//sprite->Release();
}

void clsPlayer::constructor()
{
	frame = 0;
	xPos = (SCREEN_WIDTH-FRAMEWIDTH)/2;
	yPos = SCREEN_HEIGHT-FRAMEHEIGHT;
	hp = 5;
}

/*void clsPlayer::setPicture(LPDIRECT3DDEVICE9 dev)
{
	D3DXCreateTextureFromFileEx(dev,    // the device pointer
                                L"data/plane.png",    // the file name
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
}*/

void clsPlayer::draw(SDL_Surface* screen)
{
	/*if(hp == 0)
	{
		rotate+=0.18;
	}
	D3DXVECTOR2 spriteCentre=D3DXVECTOR2(xPos+16,yPos+16);
	D3DXVECTOR2 scaling(1.0f,1.0f);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat,NULL,0.0,&scaling,&spriteCentre,rotate,0);
	spt->SetTransform(&mat);

    if(frame == NUMFRAMES) frame=0;
    if(frame < NUMFRAMES) frame++;     // if we aren't on the last frame, go to the next frame

	    // calculate the x-position
    frameXPos = frame * FRAMEWIDTH;
	SetRect(&part, frameXPos, 0, (frameXPos + FRAMEWIDTH), FRAMEHEIGHT);

	D3DXVECTOR3 center(0.0f, 0.0f, 0.0f); // center at the upper-left corner
    D3DXVECTOR3 position(xPos,yPos,0);
    spt->Draw(sprite, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));
	*/
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

void clsPlayer::move(int direction)
{
	if(direction == 0 && yPos > 0)//up
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
	else if(direction == 1 && yPos < (SCREEN_HEIGHT-FRAMEHEIGHT))//down
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
	else if(direction == 2 && xPos > 0)//left
	{
		if(xPos < SPEED)
		{
			xPos = 0;
		}
		else
		{
			xPos-=SPEED;
		}
	}
	else if(direction == 3 && xPos < (SCREEN_WIDTH-(FRAMEWIDTH-1)))//right - Note: plane is 1 pixel off on the right side
	{
		if(xPos > ((SCREEN_WIDTH-(FRAMEWIDTH-1))-SPEED))
		{
			xPos = (SCREEN_WIDTH-(FRAMEWIDTH-1));
		}
		else
		{
		xPos+=SPEED;
		}
	}
	else if(direction == 5 && yPos < (SCREEN_HEIGHT-FRAMEHEIGHT))//downward drift
	{
		if(yPos > ((SCREEN_HEIGHT-FRAMEHEIGHT)-(SPEED/4)))
		{
			yPos=(SCREEN_HEIGHT-FRAMEHEIGHT);
		}
		else
		{
			yPos+=(SPEED/4);
		}
	}
}

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

bool clsPlayer::collide(float AsteroidX, float AsteroidY, int damage)
{
	if((xPos+32) > AsteroidX && xPos < (AsteroidX+32))
	{
		if(yPos < (AsteroidY + 32) && (yPos+32) > AsteroidY)
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