///////////////////////////////////////////////////////////////
///////////////////////SteveShmup v0.09///////////////////////
////////////////////////by Luke Mercuri////////////////////////
//////////////////////////25/05/2010///////////////////////////
///////////////////////////////////////////////////////////////

#include "main.h" 

// the entry point for any Windows program
int main(int argc, char* args[])
{
	int quit = 0;
	nsrand((unsigned)time(NULL)); //generates random number based on time as rand()

    // enter the main loop

    SDL_Init(SDL_INIT_VIDEO);
    keystate = SDL_GetKeyState(NULL);
    TTF_Init();

    font = TTF_OpenFont("data/TerminusTTF-4.39.ttf", 12);

   	if(font == NULL)
   	{
   		std::cout << "error loading font\n";
   	}

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    SDL_ShowCursor(SDL_DISABLE);

	restartGame();

    while(!quit)
    {

        SDL_PumpEvents();

    	if(keystate[SDLK_RETURN] && !gameOver)
		{
			//wait until key up else game doesn't pause
			while(keystate[SDLK_RETURN])
			{
				SDL_PumpEvents();
			}

			gamePaused = !gamePaused;
		}

        if(!gamePaused)
        {
			if(!gameOver)
			{
				//this gross bool stops it just giving you infinite health before you change scores
				if(!gotHealthPack && !(score%HEALTHBONUS) && score)
				{
					plane.upHP(1);
					gotHealthPack == true;
				}
				else if(score%HEALTHBONUS)
				{
					gotHealthPack = false;
				}

				if(!bonusAmmo && !(score%BULLETBONUS) && score)
				{
					bonusAmmo = BONUSAMMO;
					bulletFreq = 1;
				}


				//debug
				std::cout << "bonusAmmo: " << bonusAmmo << "\nBONUSAMMO: " << BONUSAMMO << "\nScore: " << score << "\nBULLETBONUS: " << BULLETBONUS << "\n(score%BULLETBONUS): " << (score%BULLETBONUS) << "\n\n";

				snprintf(scoreText, 99, "Score: %i", score);
				count();
				moveObjects();
				killObjects();
			}
			else
			{
				loseGame();
				if(keystate[SDLK_RETURN])
				{
					//wait until key up else game pauses
					while(keystate[SDLK_RETURN])
					{
						SDL_PumpEvents();
					}
					restartGame();
				}
			}

			render_frame();
		}

        // check the 'L' or 'R' shoulder buttons
        if((keystate[SDLK_TAB]) && (keystate[SDLK_BACKSPACE])){
            quit = 1;
        }
 
    }

    //clean things up a little
    SDL_FreeSurface(screen);
    if(asteroidHead != NULL)
	{
		asteroidHead->freeList();
		asteroidHead = NULL;
	}
	if(bulletHead != NULL)
	{
		bulletHead->freeList();
		bulletHead = NULL;
	}

	//TTF_Quit();

 	SDL_Quit();

    return 0;
}


// this is the function used to render a single frame
void render_frame(void)
{
		////////////////////////////////////////////////////////
		//draw all game objects here////////////////////////////
		////////////////////////////////////////////////////////
		
		bg.draw(screen);

		//start linked lists

		//place AsteroidTemp at the start of the list
		clsAsteroid* asteroidTemp;
		asteroidTemp = asteroidHead;
		while(asteroidTemp!=NULL)
		{
			asteroidTemp->draw(screen);
			if(!gameOver)
			{
				asteroidTemp->move();
			}
			//move to the next object in list
			asteroidTemp=asteroidTemp->asteroidNext;
		}	
		//place bulletTemp at the start of the list
		clsBullet* bulletTemp;
		bulletTemp = bulletHead;
		while(bulletTemp!=NULL)
		{
			bulletTemp->draw(screen);
			if(!gameOver)
			{
				bulletTemp->move(DIR_UP);
			}
			//move to the next object in list
			bulletTemp=bulletTemp->bulletNext;
		}	

		//end linked list
		plane.draw(screen);
		hp.draw(screen, plane.getHP());

	keepScore();

    SDL_Flip(screen);

    //SDL_Delay(DELAY);

    return;
}

void count()
{
	counter++;
	frequency -= 0.001;
	if(frequency < 1)
	{
		frequency = 1;
	}
}
void moveObjects()
{


	bg.move();

	if(keystate[SDLK_UP])
	{
		plane.move(DIR_UP);
	}
	else if(keystate[SDLK_DOWN])
	{
		plane.move(DIR_DOWN);
	}
	else
	{
		if(counter%2)
		{
			plane.move(DIR_DRIFT);
		}
	}
	if(keystate[SDLK_LEFT])
	{
		plane.move(DIR_LEFT);
	}
	if(keystate[SDLK_RIGHT])
	{
		plane.move(DIR_RIGHT);
	}
	if(!(counter%bulletFreq) && keystate[SDLK_LCTRL])
	{
		addBulletToList(plane.getX(), plane.getY());
	}
	if(((counter)%(int)frequency)==0)
	{
		addAsteroidToList();
	}
}

void killObjects()
{
	clsBullet* bulletTemp;
	clsAsteroid* asteroidTemp;
	asteroidTemp = asteroidHead;
	while(asteroidTemp!=NULL)
	{
		bulletTemp = bulletHead;
		while(bulletTemp!=NULL)
		{
			asteroidTemp->takeDamage(bulletTemp->collide(asteroidTemp->getX(),asteroidTemp->getY())); //checks all bullets for collisions with all asteroids
			bulletTemp=bulletTemp->bulletNext;
		}
		gameOver = plane.collide(asteroidTemp->getX(),asteroidTemp->getY(), plane.getHP());
		asteroidTemp=asteroidTemp->asteroidNext;		//move to the next object in list
	}	
	removeBulletFromList();
	removeAsteroidFromList();
}

//////////////////////////////////////////////
///Annoying, confusing Linked List Code///////
//////////////////////////////////////////////
void addBulletToList(float x, float y)
{
	//create new bullet object
	clsBullet* bulletTemp;
	bulletTemp = new clsBullet;
	bulletTemp->setXY(x,y);

	if(bonusAmmo > 0)
	{
		bonusAmmo--;
	}
	else
	{
		bulletFreq = BULLETFREQ;
	}

	//add new bullet to start of linked list
	bulletTemp->bulletNext = bulletHead;
	bulletHead = bulletTemp;
}

void removeBulletFromList()
{
	//if there is atleast one item in the list
	if(bulletHead!=NULL)
	{
		clsBullet* bulletCurrent;
		clsBullet* bulletPrevious;
		//point to first object in list
		bulletPrevious=bulletHead;
		//point to second object in list
		bulletCurrent=bulletHead->bulletNext;

		//check first object in list
		if(bulletPrevious->checkDead())
		{
			//remove this object from list and RAM
			bulletHead = bulletCurrent;			
			delete bulletPrevious;
			return;
		}

		//while not at the end of the list
		while(bulletCurrent!=NULL)
		{
			//if the object is dead
			if(bulletCurrent->checkDead())
			{				
				//remove this object from list and RAM
				//bulletCurrent->bulletNext = bulletPrevious;
				bulletPrevious->bulletNext = bulletCurrent->bulletNext;			
				delete bulletCurrent;
				return;
			}
			//point to next object in list
			bulletPrevious=bulletCurrent;
			bulletCurrent=bulletCurrent->bulletNext;
		}
	}		
}

void addAsteroidToList()
{
	//create new asteroid object
	clsAsteroid* asteroidTemp;
	
	asteroidTemp = new clsAsteroid;
	//add new asteroid to start of linked list
	asteroidTemp->asteroidNext = asteroidHead;
	asteroidHead = asteroidTemp;
	
}

void removeAsteroidFromList()
{
	//if there is atleast one item in the list
	if(asteroidHead!=NULL)
	{
		clsAsteroid* asteroidCurrent;
		clsAsteroid* asteroidPrevious;
		//point to first object in list
		asteroidPrevious=asteroidHead;
		//point to second object in list
		asteroidCurrent=asteroidHead->asteroidNext;

		//check first object in list
		if(asteroidPrevious->checkDead())
		{
			if(asteroidCurrent->deathType == 1)
			{
				gameOver = plane.takeDamage(1);
			}
			else
			{
				score += 10;
			}
			//remove this object from list and RAM
			asteroidHead = asteroidCurrent;			
			delete asteroidPrevious;
			return;
		}

		//while not at the end of the list
		while(asteroidCurrent!=NULL)
		{
			//if the object flies offscreen
			if(asteroidCurrent->checkDead())
			{		
				if(asteroidCurrent->deathType == 1)
				{
					gameOver = plane.takeDamage(1);
				}
				else
				{
					score += 10;
				}
				//remove this object from list and RAM
				asteroidPrevious->asteroidNext = asteroidCurrent->asteroidNext;			
				delete asteroidCurrent;
				return;
			}
			//point to next objects in list
			asteroidPrevious=asteroidCurrent;
			asteroidCurrent=asteroidCurrent->asteroidNext;
		}
	}		
}

void loseGame()
{
	gamePaused = false;
	scorePos.x = GAMEOVEROFFSET;
    scorePos.w = SCREEN_WIDTH;
	sprintf(scoreText, "RIP | L+R to quit | Start to replay | Score: %i", score);
}

void restartGame()
{
	if(asteroidHead != NULL)
	{
		asteroidHead->freeList();
		asteroidHead = NULL;
	}
	if(bulletHead != NULL)
	{
		bulletHead->freeList();
		bulletHead = NULL;
	}
	plane.reset();
	gameOver = false;
	gamePaused = false;
	bulletFreq = BULLETFREQ;
	bonusAmmo = 0;
	frequency = FREQUENCY;
	counter = 1;
	score = 0;
	scorePos.x = (SCREEN_WIDTH/3)+SCOREOFFSET;
    scorePos.y = 0;
    scorePos.h = 12;
    scorePos.w = 40;
}

void keepScore()
{
    if(font != NULL)
    {
    	text = TTF_RenderText_Solid(font, scoreText, text_color);
    	SDL_BlitSurface(text, NULL, screen, &scorePos);
	}
}