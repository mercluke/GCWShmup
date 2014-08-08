///////////////////////////////////////////////////////////////
///////////////////////SteveShmup v0.10///////////////////////
////////////////////////by Luke Mercuri////////////////////////
//////////////////////////08/08/2014///////////////////////////
///////////////////////////////////////////////////////////////

#include "main.h" 


//enter the main loop
int main(int argc, char* args[])
{
	int quit = 0;
	srand((unsigned)time(NULL)); //seed rand()

	//file we store high score in
	scoreFile = fopen(".GCWShmup","rb");
	if(scoreFile != NULL)
	{
		//if didn't read out an int from file then no current high score
		if(fscanf(scoreFile, "%d\n", &highScore) != 1)
		{
			highScore = 0;
		}
		fclose(scoreFile);
	}

	//setup sdl video/input/font rendering
    SDL_Init(SDL_INIT_VIDEO);
    keystate = SDL_GetKeyState(NULL);
    TTF_Init();

    //try to load font from file
    font = TTF_OpenFont("data/TerminusTTF-4.39.ttf", 12);
   	if(font == NULL)
   	{
   		std::cout << "error loading font\n";
   	}

   	//set screen resolution and stop sdl showing a mouse pointer
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    SDL_ShowCursor(SDL_DISABLE);

    //initial assorted variables
	restartGame();

    while(!quit)
    {

    	//check keypresses
        SDL_PumpEvents();

    	if(keystate[SDLK_RETURN] && !gameOver)
		{
			pauseGame();
		}


        if(!gamePaused)
        {
        	//still playing
			if(!gameOver)
			{
				bonusItems();
				sprintf(scoreText, "Score: %i", score);
				scorePos.x = (SCREEN_WIDTH/2)-((CHARWIDTH/2)*strlen(scoreText));
				count();
				moveObjects();
				killObjects();
			}
			//player died
			else
			{
				loseGame();

				//restart game by pressing start/enter
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

			//draw to screen
			render_frame();
		}

        // check the 'L' and 'R' shoulder buttons to quit
        if((keystate[SDLK_TAB] && keystate[SDLK_BACKSPACE]) || keystate[SDL_QUIT])
        {
            quit = 1;
        }
 
    }

    //clean things up a little before exiting
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


	TTF_Quit();

 	SDL_Quit();

    return 0;
}

void pauseGame()
{
	//diplay "-paused-" on the screen
	if(font != NULL)
	{
		highScorePos.x = (SCREEN_WIDTH/2)-((CHARWIDTH/2)*strlen("-paused-"));
		text = TTF_RenderText_Solid(font, "-paused-", text_color);
		SDL_BlitSurface(text, NULL, screen, &highScorePos);
		SDL_Flip(screen);
	}

	//wait until key up else game doesn't pause
	while(keystate[SDLK_RETURN])
	{
		SDL_PumpEvents();
	}

	gamePaused = !gamePaused;
}

//Bonus stuff
void bonusItems()
{
	//this gross bool stops it just giving you infinite health before you change scores
	if(!gotHealthPack && !(score%HEALTHBONUS) && score)
	{
		plane.upHP(1);
		gotHealthPack == true;
	}
	/*once score has changed the user no longer 
	  "has" the healthpack and so can get it 
	  next time they reach score milestone*/
	else if(score%HEALTHBONUS)
	{
		gotHealthPack = false;
	}

	//Laser powerup
	if(!(score%BULLETBONUS) && score)
	{
		bonusAmmo = BONUSAMMO;
		bulletFreq = 1;
	}
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

	//paint the image to screen
    SDL_Flip(screen);

    //wait before next frame
    SDL_Delay(DELAY);

    return;
}

//longer game goes, more frequntly asteroids spawn
void count()
{
	counter++;
	frequency -= 0.001;
	if(frequency < 1)
	{
		frequency = 1;
	}
}

//moves all objects on screen
void moveObjects()
{

	//scroll background
	bg.move();

	//move player's plane
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

	//shoot bullets
	if(!(counter%bulletFreq) && (keystate[SDLK_SPACE] || keystate[SDLK_LCTRL]) )
	{
		addBulletToList(plane.getX(), plane.getY());
	}

	//spawn asteroid
	if(((counter)%(int)frequency)==0)
	{
		addAsteroidToList();
	}
}

//check collisions or offscreen
void killObjects()
{
	clsBullet* bulletTemp;
	clsAsteroid* asteroidTemp;
	asteroidTemp = asteroidHead;
	//walk thround entire asteroid list
	while(asteroidTemp!=NULL)
	{
		bulletTemp = bulletHead;
		//walk through entire bullet list
		while(bulletTemp!=NULL)
		{
			//did bullet hit asteroid?
			asteroidTemp->takeDamage(bulletTemp->collide(asteroidTemp->getX(),asteroidTemp->getY())); //checks all bullets for collisions with all asteroids
			bulletTemp=bulletTemp->bulletNext;
		}
		//did player hit asteroid?
		gameOver = plane.collide(asteroidTemp->getX(),asteroidTemp->getY(), plane.getHP());
		asteroidTemp=asteroidTemp->asteroidNext;		//move to the next object in list
	}	
	removeBulletFromList();
	removeAsteroidFromList();
}

/////////////////////////////////////////////////////
///Annoying, not so confusing Linked List Code///////
/////////////////////////////////////////////////////
void addBulletToList(float x, float y)
{
	//create new bullet object
	clsBullet* bulletTemp;
	bulletTemp = new clsBullet;
	bulletTemp->setXY(x,y);

	//decrease powerup ammo if player has it
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


//tell player they screwed up, save/display highscore
void loseGame()
{
	gamePaused = false;
	sprintf(scoreText, "RIP | L+R to quit | Start to replay | Score: %i", score);
	scorePos.x = (SCREEN_WIDTH/2)-((CHARWIDTH/2)*strlen(scoreText));
    scorePos.w = SCREEN_WIDTH;

    //w00t, new highscore
	if(score > highScore)
	{
		highScore = score;

		scoreFile = fopen(".GCWShmup", "wb");
		if(scoreFile != NULL)
		{
			fprintf(scoreFile, "%d\n", highScore);
			fclose(scoreFile);
			sprintf(highScoreText, "New High Score!   %i", highScore);
		}
	}
}

//initialise variables for start of game
void restartGame()
{
	//free any existing asteroid and bullets
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
	//give player back their hp and place them at bottom of screen
	plane.reset();
	gameOver = false;
	gamePaused = false;
	bulletFreq = BULLETFREQ;
	bonusAmmo = 0;
	frequency = FREQUENCY;
	counter = 1;
	score = 0;
	scorePos.x = (SCREEN_WIDTH/2)-((CHARWIDTH/2)*strlen(scoreText));
    scorePos.y = 0;
    scorePos.h = 12;
    scorePos.w = 40;
    sprintf(highScoreText, "High Score:   %i", highScore);
    highScorePos.x = (SCREEN_WIDTH/2)-((CHARWIDTH/2)*strlen(highScoreText));
    highScorePos.y = SCREEN_HEIGHT/2;
    highScorePos.h = 12;
    highScorePos.w = (SCREEN_WIDTH-highScorePos.y);
}

//render the score text
void keepScore()
{
    if(font != NULL)
    {
    	text = TTF_RenderText_Solid(font, scoreText, text_color);
    	SDL_BlitSurface(text, NULL, screen, &scorePos);

    	//display highscore at end of game
    	if(gameOver)
    	{
    		highScorePos.x = (SCREEN_WIDTH/2)-((CHARWIDTH/2)*strlen(highScoreText));
	    	text = TTF_RenderText_Solid(font, highScoreText, text_color);
			SDL_BlitSurface(text, NULL, screen, &highScorePos);
		}
	}
}