#ifndef MAIN_H
#define MAIN_H
#include "globalStuff.h"
#include "clsPlayer.h"
#include "clsBullet.h"
#include "clsAsteroid.h"
#include "clsHealthBar.h"
#include "clsBackGround.h"

// define the screen resolution and keyboard macros
SDL_Surface* screen = NULL;
SDL_Surface* text;
SDL_Color text_color = {255,255,255};
TTF_Font* font = NULL;
clsPlayer plane;
clsBackGround bg;
clsHealthBar hp;
clsAsteroid* asteroidHead;
clsBullet* bulletHead;
FILE* scoreFile;


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
void bonusItems();
void pauseGame();



int counter; //used for gravity and the like...  - well not gravity since it's bird's eye view but still... the plane drifts slowly downwards when no buttons are pressed
float frequency;
bool gameOver;
bool gamePaused;
int score = 0;
int highScore = 0;
bool gotHealthPack = false;
int bonusAmmo;
int bulletFreq; //higher number == lower damage
char scoreText[100];
char highScoreText[100];
SDL_Rect scorePos;
SDL_Rect highScorePos;
Uint8 *keystate;
#endif