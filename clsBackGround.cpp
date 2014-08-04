#include "StdAfx.h"
#include "clsBackGround.h"

clsBackGround::clsBackGround(void)
{
	constructor();
}

clsBackGround::~clsBackGround(void)
{
	sprite->Release();
}

void clsBackGround::setPicture(LPDIRECT3DDEVICE9 dev)
{
	D3DXCreateTextureFromFileEx(dev,    // the device pointer
                                L"data/back_4-3.png",    // the file name
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
}

void clsBackGround::draw(LPD3DXSPRITE spt)
{
	D3DXVECTOR2 spriteCentre=D3DXVECTOR2(32.0f,32.0f);
	D3DXVECTOR2 scaling(1.0f,1.0f);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat,NULL,0.0,&scaling,&spriteCentre,0,0);
	spt->SetTransform(&mat);

	D3DXVECTOR3 center(0.0f, 0.0f, 0.0f); // center at the upper-left corner
	D3DXVECTOR3 position(0, yPos, 0);
    spt->Draw(sprite, NULL, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));
	D3DXVECTOR3 position2(0, yPos2, 0);
    spt->Draw(sprite, NULL, &center, &position2, D3DCOLOR_ARGB(255, 255, 255, 255)); //not sure if doing this as opposed to having a 2x height image would be faster but it will save memory
}

void clsBackGround::move()
{
	if(yPos > (0-(SPEED*0.4)))
	{
		yPos = (0-HEIGHT);
		yPos2 = 0;
	}
	else
	{
		yPos  += (SPEED*0.4);
		yPos2 += (SPEED*0.4);
	}
}

void clsBackGround::constructor()
{
	yPos = (0-HEIGHT);
	yPos2 = 0;
}