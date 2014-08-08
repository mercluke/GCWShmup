#ifndef GLOBALSTUFF_H
#define GLOBALSTUFF_H
#define SCREEN_WIDTH		320
#define SCREEN_HEIGHT		240
#define SPEED				1.0
#define FULLHEALTH			5
#define	DIR_UP				0
#define	DIR_DOWN			1
#define	DIR_LEFT			2
#define	DIR_RIGHT			3
#define	DIR_DRIFT			4
#define DELAY 				4
//Starting value for asteroid spawn frequency
#define FREQUENCY 			100
//Starting value for bullet firing rate
#define BULLETFREQ 			12
//mod score by this for when to get health bonus
#define HEALTHBONUS 		200
//mod score by this for when to get bullet powerup
#define BULLETBONUS 		1000
//how many bullets to fire before losing powerup
#define BONUSAMMO 			500
//rough guess of a character pixel width
#define CHARWIDTH 			6

#include <iostream>
#include <ctime>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#endif