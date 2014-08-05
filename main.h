#ifndef MAIN_H
#define MAIN_H
#include "globalConstants.h"
#include "clsPlayer.h"
#include "clsBullet.h"
#include "clsAsteroid.h"
#include "clsHealthBar.h"
#include "clsBackGround.h"
#define KEY_DOWN(x) (event.type == SDL_KEYDOWN && event.key.keysym.sym == x)
#define DELAY 20


// define the screen resolution and keyboard macros
SDL_Event event;
SDL_Surface* screen = NULL;
SDL_Surface* text;
SDL_Color text_color = {255,255,255};
TTF_Font* font = NULL;
clsPlayer plane;
clsBackGround bg;
clsHealthBar hp;
clsAsteroid* asteroidHead;
clsBullet* bulletHead;

// global declarations
/*LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
LPDIRECT3DTEXTURE9 loseSprite; //you lose
LPD3DXSPRITE d3dspt;    // the pointer to our Direct3D Sprite interface
LPD3DXFONT dxfont;    // the pointer to the font object
CSoundManager* g_pSoundManager; //pointer to Sound Manager object*/

// function prototypes
//void initD3D(HWND hWnd);    // sets up and initializes Direct3D
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
bool gameOver;
int score;
bool gotHealthPack = false;
static const int HEALTHBONUS = 50;
int damageModifier; //higher number == lower damage
char scoreText[100];
#endif