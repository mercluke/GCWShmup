///////////////////////////////////////////////////////////////
///////////////////////SteveShmup v0.09///////////////////////
////////////////////////by Luke Mercuri////////////////////////
//////////////////////////05/25/2010///////////////////////////
///////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "main.h" 

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    HWND hWnd;
    WNDCLASSEX wc; 

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX); 
    wc.style = CS_HREDRAW | CS_VREDRAW; 
    wc.lpfnWndProc = (WNDPROC)WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"WindowClass";

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(NULL, L"WindowClass", L"SteveShmup",
                          WS_OVERLAPPEDWINDOW/*WS_EX_TOPMOST | WS_POPUP*/, 0, 0, 
						  SCREEN_WIDTH, SCREEN_HEIGHT,  
                          NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);

    // set up and initialize Direct3D
    initD3D(hWnd);

			//Direct Sound
	g_pSoundManager = new CSoundManager;
	g_pSoundManager->Initialize( hWnd, DSSCL_PRIORITY );
	g_pSoundManager->SetPrimaryBufferFormat( 2, 22050, 16 );

    // enter the main loop

    MSG msg;

	restartGame();

    while(TRUE)
    {
        DWORD starting_point = GetTickCount();

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		if(!gameOver)
		{
			sprintf_s(scoreText, "Score: %i", score);
			count();
			moveObjects();
			killObjects();
		}
		else
		{
			if(KEY_DOWN(VK_RETURN))
			{
				restartGame();
			}
			loseGame();
		}
		render_frame();

        // check the 'escape' key
        if(KEY_DOWN(VK_ESCAPE))
            PostMessage(hWnd, WM_DESTROY, 0, 0);
 
        while ((GetTickCount() - starting_point) < 25);
    }
 
    // clean up DirectX and COM
    cleanD3D();

    return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch(message)
    {
        // this message is read when the window is closed
        case WM_DESTROY:
            {
                // close the application entirely
                PostQuitMessage(0);
                return 0;
            } break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
} 

void initD3D(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dpp;

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = true;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferWidth = SCREEN_WIDTH;
    d3dpp.BackBufferHeight = SCREEN_HEIGHT;


    // create a device class using this information and the info from the d3dpp stuct
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);

    D3DXCreateSprite(d3ddev, &d3dspt);    // create the Direct3D Sprite object
	bg.setPicture(d3ddev);
    plane.setPicture(d3ddev);
	hp.setPicture(d3ddev);

	D3DXCreateFont(d3ddev,    // the D3D Device
           25,    // font height of 30
           0,    // default font width
           FW_NORMAL,    // font weight
           1,    // not using MipLevels
           true,    // italic font
           DEFAULT_CHARSET,    // default character set
           OUT_DEFAULT_PRECIS,    // default OutputPrecision,
           DEFAULT_QUALITY,    // default Quality
           DEFAULT_PITCH | FF_DONTCARE,    // default pitch and family
           L"Arial",    // use Facename Arial
           &dxfont);    // the font object


    return;
}

// this is the function used to render a single frame
void render_frame(void)
{
    // clear the window to black
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    d3ddev->BeginScene();    // begins the 3D scene

    d3dspt->Begin(D3DXSPRITE_ALPHABLEND);    // // begin sprite drawing with transparency

		
		////////////////////////////////////////////////////////
		//draw all game object here/////////////////////////////
		////////////////////////////////////////////////////////
		
		bg.draw(d3dspt);//has to be drawn first

		//start linked lists

		//place AsteroidTemp at the start of the list
		clsAsteroid* asteroidTemp;
		asteroidTemp = asteroidHead;
		while(asteroidTemp!=NULL)
		{
			asteroidTemp->draw(d3dspt);
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
			bulletTemp->draw(d3dspt);
			if(!gameOver)
			{
				bulletTemp->move(0);
			}
			//move to the next object in list
			bulletTemp=bulletTemp->bulletNext;
		}	

		//end linked list
		plane.draw(d3dspt);
		hp.draw(d3dspt, plane.getHP());

    d3dspt->End();    // end sprite drawing

	keepScore();

    d3ddev->EndScene();    // ends the 3D scene

    d3ddev->Present(NULL, NULL, NULL, NULL);

    return;
}


// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
    d3ddev->Release();
    d3d->Release();

    return;
}

void count()
{
	counter++;
	frequency -= 0.01;
	if(frequency < 1)
	{
		frequency = 1;
	}
	frequency2 = frequency;
}
void moveObjects()
{
	if(KEY_DOWN(VK_UP))
	{
		plane.move(0);
	}
	else if(KEY_DOWN(VK_DOWN))
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
	if(KEY_DOWN(VK_LEFT))
	{
		plane.move(2);
	}
	if(KEY_DOWN(VK_RIGHT))
	{
		plane.move(3);
	}
	if(((counter%4)==0) && KEY_DOWN(VK_SPACE))
	{
		addBulletToList(plane.getX(), plane.getY());
	}
	if((counter%frequency2)==0)
	{
		addAsteroidToList();
	}
	bg.move();
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
			asteroidTemp->takeDamage(bulletTemp->collide(asteroidTemp->getX(),asteroidTemp->getY()), g_pSoundManager); //checks all bullets for collisions with all asteroids
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
	bulletTemp->setPicture(d3ddev);
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
		asteroidTemp = new clsAsteroid2;
	}
	asteroidTemp->setPicture(d3ddev);

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
	sprintf(scoreText, "You Lose, Press ESC and Go Away\n \(or press ENTER to lose again\)\nScore: %i", score);
}

void restartGame()
{
	asteroidHead = NULL;
	plane.constructor();
	bulletHead = NULL;
	bg.constructor();
	gameOver = false;
	frequency = 80;
	counter = 1;
	score = 0;
}

void keepScore()
{
	// create a RECT to contain the text
    static RECT textbox; SetRect(&textbox, 0, 0, SCREEN_WIDTH, 75);
	dxfont->DrawTextA(NULL,
                      scoreText,
                      -1,
                      &textbox,
                      DT_CENTER | 0,
                      D3DCOLOR_ARGB(255, 255, 255, 255));
}