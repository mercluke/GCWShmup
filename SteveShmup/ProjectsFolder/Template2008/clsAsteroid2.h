#pragma once
#include "clsAsteroid.h"

class clsAsteroid2 :
	public clsAsteroid
{
public:
	clsAsteroid2(void);
	~clsAsteroid2(void);
	void setPicture(LPDIRECT3DDEVICE9 dev);
};
