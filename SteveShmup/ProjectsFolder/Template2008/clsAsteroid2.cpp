#include "clsAsteroid2.h"

clsAsteroid2::clsAsteroid2(void)
{
	hp = 3;
}

clsAsteroid2::~clsAsteroid2(void)
{
}

void clsAsteroid2::setPicture(LPDIRECT3DDEVICE9 dev)
{
	D3DXCreateTextureFromFileEx(dev,    // the device pointer
                                L"data/asteroid2.png",    // the file name
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