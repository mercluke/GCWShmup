//#include "StdAfx.h"
#include "clsAsteroid.h"


clsAsteroid::clsAsteroid(void)
{
	yPos = (0-SCREEN_HEIGHT);
	//srand((unsigned)time(0)); //generates random number based on time as rand()
	xPos = (rand()%(SCREEN_WIDTH-WIDTH)); //starts at a random horizontal position to make games a little less boring
	asteroidNext=NULL;
	rotation = 0;
	dead = false;
	hp = 5;
}

clsAsteroid::~clsAsteroid(void)
{
	//sprite->Release();
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

/*void clsAsteroid::setPicture(LPDIRECT3DDEVICE9 dev)
{
	D3DXCreateTextureFromFileEx(dev,    // the device pointer
                                L"data/asteroid1.png",    // the file name
                                D3DX_DEFAULT,    // default width
                                D3DX_DEFAULT,    // default height
                                D3DX_DEFAULT,    // no mip mapping
                                NULL,    // regular usage
                                D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
                                D3DPOOL_MANAGED,    // typical memory handling
                                D3DX_DEFAULT,    // no filtering
                                D3DX_DEFAULT,    // no mip filtering
                                D3DCOLOR_XRGB(255, 0, 255),    // hot pink
                                NULL,    // no image info struct
                                NULL,    // not using 256 colors
                                &sprite);    // load to sprite
}*/

/*void clsAsteroid::draw(LPD3DXSPRITE spt)
{
	D3DXVECTOR2 spriteCentre=D3DXVECTOR2(32.0f,32.0f);
	D3DXVECTOR2 scaling(1.0f,1.0f);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat,NULL,0.0,&scaling,&spriteCentre,rotation,0);
	//rotation+=0.01;
	spt->SetTransform(&mat);

	D3DXVECTOR3 center(0.0f, 0.0f, 0.0f); // center at the upper-left corner
    D3DXVECTOR3 position(xPos,yPos,0);
    spt->Draw(sprite, NULL, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));
	
}*/


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

void clsAsteroid::takeDamage(bool damage/*, CSoundManager* SoundManager*/)
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
				//sound stuff
		//create a pointer called pSound
		//CSound* pSound;

		//make pSound point to bounce.wav
		//SoundManager->Create( &pSound, L"data/damage.wav", 0, GUID_NULL );

		//play bounce.wav
		//pSound->Play(0,0);
	}

}

