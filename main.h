#ifndef MAIN_H
#define MAIN_H
#include "globalStuff.h"
#include "clsPlayer.h"
#include "clsBullet.h"
#include "clsAsteroid.h"
#include "clsHealthBar.h"
#include "clsBackGround.h"
#define DELAY 4

//Starting value for asteroid spawn frequency
#define FREQUENCY 100
//Starting value for bullet firing rate
#define BULLETFREQ 12
//number of pixels game over message is from edge of screen
#define GAMEOVEROFFSET 17
//number of pixel score text is from 3rd of screen
#define SCOREOFFSET (SCREEN_WIDTH/3)+30
//mod score by this for when to get health bonus
#define HEALTHBONUS 200
//mod score by this for when to get bullet powerup
#define BULLETBONUS 1000
//how many bullets to fire before losing powerup
#define BONUSAMMO 500


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



int counter; //used for gravity and the like...  - well not gravity since it's bird's eye view but still... the plane drifts slowly downwards when no buttons are pressed
float frequency;
bool gameOver;
bool gamePaused;
int score = 0;
int highScore = 0;
bool gotHealthPack = false;
int bonusAmmo;
//static const int FREQMODIFIER = 10;
int bulletFreq; //higher number == lower damage
char scoreText[100];
char highScoreText[100];
SDL_Rect scorePos;
SDL_Rect highScorePos;
Uint8 *keystate;
#endif