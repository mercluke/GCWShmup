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


    /*HWND hWnd;
    WNDCLASSEX wc; 

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX); 
    wc.style = CS_HREDRAW | CS_VREDRAW; 
    wc.lpfnWndProc = (WNDPROC)WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"WindowClass";

    RegisterClassEx(&wc);*/

    //hWnd = CreateWindowEx(NULL, L"WindowClass", L"SteveShmup",
    //                      WS_OVERLAPPEDWINDOW/*WS_EX_TOPMOST | WS_POPUP*/, 0, 0, 
	//					  SCREEN_WIDTH, SCREEN_HEIGHT,  
    //                      NULL, NULL, hInstance, NULL);

    //ShowWindow(hWnd, nCmdShow);

    // set up and initialize Direct3D
    //initD3D(hWnd);

    // enter the main loop

    //MSG msg;

    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    SDL_ShowCursor(SDL_DISABLE);

	restartGame();

    while(!quit)
    {

        //DWORD starting_point = GetTickCount();

        /*if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }*/

        SDL_PollEvent(&event);

        if(event.type == SDL_QUIT)
        {
        	quit = 1;
        }

		if(!gameOver)
		{
			snprintf(scoreText, 99, "Score: %i", score);
			count();
			moveObjects();
			killObjects();
		}
		else
		{
			if(KEY_DOWN(SDLK_RETURN))
			{
				restartGame();
			}
			loseGame();
		}
		render_frame();

        // check the 'select' key
        if((KEY_DOWN(SDLK_TAB)) || (KEY_DOWN(SDLK_BACKSPACE))){
            quit = 1;
        }
 
    }

    SDL_FreeSurface(screen);

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
				bulletTemp->move(0);
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


// this is the function that cleans up Direct3D and COM
/*void cleanD3D(void)
{
    d3ddev->Release();
    d3d->Release();

    return;
}*/

void count()
{
	counter++;
	frequency -= 0.01;
	if(frequency < 1)
	{
		frequency = 1;
	}
}
void moveObjects()
{
	if(KEY_DOWN(SDLK_UP))
	{
		plane.move(0);
	}
	else if(KEY_DOWN(SDLK_DOWN))
	{
		plane.move(1);
	}
	else
	{
		if(counter%2==0)
		{
		plane.move(5);
		}
	}
	if(KEY_DOWN(SDLK_LEFT))
	{
		plane.move(2);
	}
	if(KEY_DOWN(SDLK_RIGHT))
	{
		plane.move(3);
	}
	if(((counter%4)==0) && KEY_DOWN(SDLK_LCTRL))
	{
		addBulletToList(plane.getX(), plane.getY());
	}
	if((counter%(int)frequency)==0)
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
			asteroidTemp->takeDamage(bulletTemp->collide(asteroidTemp->getX(),asteroidTemp->getY())/*, g_pSoundManager*/); //checks all bullets for collisions with all asteroids
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
	//bulletTemp->setPicture(d3ddev);
	bulletTemp->setXY(x,y);

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
			//point to next objects in list
			bulletPrevious=bulletCurrent;
			bulletCurrent=bulletCurrent->bulletNext;
		}
	}		
}

void addAsteroidToList()
{
	//create new asteroid object
	clsAsteroid* asteroidTemp;
	if(counter%5 == 0)
	{
		asteroidTemp = new clsAsteroid;
	}
	else
	{
		//diff asteroid, change later
		asteroidTemp = new clsAsteroid;
	}
	//asteroidTemp->setPicture(d3ddev);

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
	sprintf(scoreText, "You Lose, Press ESC and Go Away\n (or press ENTER to lose again)\nScore: %i", score);
}

void restartGame()
{
	asteroidHead = NULL;
	plane.constructor();
	bulletHead = NULL;
	gameOver = false;
	frequency = 80;
	counter = 1;
	score = 0;
}

void keepScore()
{
	// create a RECT to contain the text
    //static RECT textbox; SetRect(&textbox, 0, 0, SCREEN_WIDTH, 75);
	//dxfont->DrawTextA(NULL,
    //                  scoreText,
    //                  -1,
    //                  &textbox,
    //                  DT_CENTER | 0,
    //                  D3DCOLOR_ARGB(255, 255, 255, 255));
}