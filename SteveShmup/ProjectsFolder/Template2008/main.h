#pragma once
#include "globalConstants.h"
#include "resource.h"
#include "clsPlayer.h"
#include "clsBullet.h"
#include "clsAsteroid.h"
#include "clsAsteroid2.h"
#include "clsHealthBar.h"
#include "clsBackGround.h"
#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <windowsx.h>


// define the screen resolution and keyboard macros
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
clsPlayer plane;
clsBackGround bg;
clsHealthBar hp;
clsAsteroid* asteroidHead;
clsBullet* bulletHead;

// global declarations
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
LPDIRECT3DTEXTURE9 loseSprite; //you lose
LPD3DXSPRITE d3dspt;    // the pointer to our Direct3D Sprite interface
LPD3DXFONT dxfont;    // the pointer to the font object
CSoundManager* g_pSoundManager; //pointer to Sound Manager object

// function prototypes
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame(void);    // renders a single frame
void cleanD3D(void);    // closes Direct3D and releases memory
void moveObjects();
void addBulletToList(float, float);
void removeBulletFromList();
void addAsteroidToList();
void removeAsteroidFromList();
void killObjects();
void count();
void loseGame(); //run once game over to alert player that they suck
void restartGame(); //run once they lose
void keepScore();



int counter; //used for gravity and the like...  - well not gravity since it's bird's eye view but still... the plane drifts slowly downwards when no buttons are pressed
float frequency;
int frequency2; // we need this second variable because mod (%) hates floats
bool gameOver;
int score;
char scoreText[100];

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);