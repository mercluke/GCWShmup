#include "StdAfx.h"
#include "clsHealthBar.h"

clsHealthBar::clsHealthBar(void)
{
}

clsHealthBar::~clsHealthBar(void)
{
	sprite->Release();
}

void clsHealthBar::setPicture(LPDIRECT3DDEVICE9 dev)
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
}

void clsHealthBar::draw(LPD3DXSPRITE spt, int hp)
{
	D3DXVECTOR2 spriteCentre=D3DXVECTOR2(32.0f,32.0f);
	D3DXVECTOR2 scaling(1.0f,1.0f);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat,NULL,0.0,&scaling,&spriteCentre,0,0);
	spt->SetTransform(&mat);

	D3DXVECTOR3 center(0.0f, 0.0f, 0.0f); // center at the upper-left corner
	SetRect(&part, 0, 0, ((160/5)*hp), 16);
	D3DXVECTOR3 positionEdge((160/5)*hp,0,0);
    spt->Draw(spriteEdge, NULL, &center, &positionEdge, D3DCOLOR_ARGB(255, 255, 255, 255));
	D3DXVECTOR3 position(0,0,0);
    spt->Draw(sprite, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));


	
}