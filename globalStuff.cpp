#include "globalStuff.h"


/**************************************************
rand() was somehow only changing once per second...
this code from http://en.wikipedia.org/wiki/Xorshift
       It's "good enough" for my purposes
***************************************************/

void nsrand(unsigned nseed)
{
	seed = nseed;
}

unsigned nrand(void) 
{
	seed ^= seed >> 12; // a
	seed ^= seed << 25; // b
	seed ^= seed >> 27; // c
	return seed * 2685821657736338717LL;
}