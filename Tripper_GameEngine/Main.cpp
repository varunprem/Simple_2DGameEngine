
#include <SDL.h>

#include "stdio.h"
#include "string.h"
#include "matrix.h"

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "Shader.h"
#include "MeshInstance.h"
#include "matrix.h"
#include <stdlib.h>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "stdio.h"
#include "InputManager.h"
#include "FrameRateController.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Transform.h"
#include "SentinelEnemy.h"
#include "GameObjectInstance.h"
#include "GameObjectManager.h"
#include "Controller.h"
#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include <windows.h>

CollisionManager* gpCollisionManager;
InputManager* gpInputManager;
GameObjectManager* gOM;
EventManager* gpEventManager;
FrameRateController* pF;
ResourceManager* rm;
SentinelEnemy* sm;
//Mix_Music *bgm = Mix_LoadMUS("");
//Mix_Chunk *sfx = Mix_LoadWAV("ShootBullet.wav");

void Wrap(GameObjectInstance* pInst);
void WrapDrones(GameObjectInstance* pInst);
void WrapSkyBox(GameObjectInstance* pInst);

using namespace std;

#define BULLET_SPEED 4.0f
// Window dimensions
const GLuint WIDTH = 1000, HEIGHT = 800;

GameObjectInstance* DanJones;
bool _gameIsOn = false;
bool _gameControl = true;
bool _controlScreen = false;
bool _gameWin = false;
bool shoot_Sentinel = true;
int count_death = 0;
FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}
#pragma comment(lib, "legacy_stdio_definitions.lib")

// The MAIN function, from here we start the application and run the game loop
int main(int argc, char* args[])
{
	int error = 0;

	// Initialize SDL
	if ((error = SDL_Init(SDL_INIT_VIDEO)) < 0)
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}

	SDL_Window *mainWindow;
	SDL_GLContext mainContext;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	
	mainWindow = SDL_CreateWindow("Main",
									SDL_WINDOWPOS_UNDEFINED,
								    SDL_WINDOWPOS_UNDEFINED,
									800,
									600,
									SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!mainWindow)
		printf("Unable to create the window\n");

	mainContext = SDL_GL_CreateContext(mainWindow);
	/*if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0)
		std::cout << "Error: "<< Mix_GetError() << std::endl;*/

	
	//OpenGL

	// Initialize GLEW to setup GL Function pointers
	glewInit();

	//Component Managers
	gpInputManager = new InputManager();
	rm = new ResourceManager();
	Controller* cm = new Controller();
	sm = new SentinelEnemy();
	 pF = new FrameRateController(60);
	gOM = new GameObjectManager();
	PhysicsManager* PM = new PhysicsManager();
	gpEventManager = new EventManager();

	gpCollisionManager = new CollisionManager();

	SDL_Surface* pWindowSurface = NULL;
	rm->LoadSurfaces();
	pWindowSurface = SDL_GetWindowSurface(mainWindow);
	gOM->LoadLevel("level1.txt");
	//Using the Shader

	//Passing values to the shader from Sprite Draw Mesh function
	Shader pShader("vertex.vs", "fragment.frag");
	pShader.Use();
	

	bool appIsRunning = true;
	// Game loop
	while (true == appIsRunning)
	{
		//pF->FrameStart();
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				appIsRunning = false;
			}
		}
		
		gpInputManager->Update();
		if (gpInputManager->IsPressed(SDL_SCANCODE_RETURN))
		{
			//_gameIsOn = true;
			_controlScreen = true;
		}
		if (gpInputManager->IsPressed(SDL_SCANCODE_S))
		{
			_gameIsOn = true;
			_controlScreen = false;
		}
		if (gpInputManager->IsPressed(SDL_SCANCODE_ESCAPE))
		{
			appIsRunning = false;
		}
		
		if (_gameControl && _gameIsOn)
		{
			pF->FrameStart();

			SDL_Event e;
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					appIsRunning = false;
				}
			}

			if (gpInputManager->IsPressed(SDL_SCANCODE_ESCAPE))
			{
				appIsRunning = false;
				_gameIsOn = false;
			}

			if (gpInputManager->IsTriggered(SDL_SCANCODE_D))
			{
				gpEventManager->drawDebug = !gpEventManager->drawDebug;
				if (gpEventManager->drawDebug) {

					glUniform1i(glGetUniformLocation(pShader.Program, "is_debug"), 1);
				}
				else {

					glUniform1i(glGetUniformLocation(pShader.Program, "is_debug"), 0);
				}
			}
			//Physics manager for body
			PM->Integrate(pF->GetFrameTime(), 0.0f, gOM);
			gpEventManager->Update((float)pF->GetFrameTime()* 0.001f);
			//Update Loop
			for (GameObjectInstance* pObj : gOM->mGameObjects)
			{
				Sprite* pSp = (Sprite*)pObj->GetComponent(COMPONENT_SPRITE);
				Component* pController = (Component *)pObj->GetComponent(COMPONENT_CONTROLLER);
				for (auto i : pObj->mComponents)
				{
					i->Update();
				}

				//Store the ship object
				if (pController)
				{
					DanJones = pObj;
				}
		//		printf("%i \n",&gOM->no_of_drones);
				if (gOM->no_of_drones <= -9)
				{
					_gameWin = true;
					_gameControl = false;
					_gameIsOn = false;
				}
			}

			//Clearing the buffer
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glEnable(GL_BLEND);
			glClear(GL_COLOR_BUFFER_BIT);


			// Send to shaders and draw Draw Loop
			for (GameObjectInstance* pObj : gOM->mGameObjects)
			{

				//Get the transformation matrice
				Transform* pTr = (Transform*)pObj->GetComponent(COMPONENT_TRANSFORM);
				Sprite* pSp = (Sprite*)pObj->GetComponent(COMPONENT_SPRITE);

				if (NULL == pTr || NULL == pSp)
				{
					continue;
				}

				//Wrapping the ship
				if (pSp->mType == DAN || pSp->mType == KILLSHOT)
				{
					Wrap(pObj);
				}
				//Wrap only drones
				/*if (pSp->mType == DRONES)
				{
					WrapDrones(pObj);
				}*/
				if (pSp->mType == SKYBOX_SCROLL)
				{
					WrapSkyBox(pObj);
				}


				//Draw Object
				pSp->DrawMesh(pShader);
			}

			SDL_GL_SwapWindow(mainWindow);

			char buffer[100];
			snprintf(buffer, sizeof buffer, "Tripper Engine -> Frame Time: %i", pF->GetFrameTime());
			SDL_SetWindowTitle(mainWindow, buffer);

			pF->FrameEnd();
		}
		rm->UpdateScreenSurface(mainWindow, pWindowSurface);
	}


	delete(gpInputManager);
	delete(rm);
	delete(gpCollisionManager);
	delete(gpEventManager);
	delete(gOM);
	delete(pF);
	delete(PM);
	delete(cm);
	SDL_GL_DeleteContext(mainContext);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
	//Mix_FreeChunk(sfx);
	//Mix_FreeMusic(bgm);

	/*bgm = nullptr;
	sfx = nullptr;

	Mix_Quit();
	SDL_Quit();*/

	//getchar();
	return 0;
}

void Wrap(GameObjectInstance* pInst)
{
	Transform* pTr = (Transform*)pInst->GetComponent(COMPONENT_TRANSFORM);

	if (pTr->mPosition.x > 1.6f || pTr->mPosition.x < -1.15f)
	{
		pTr->mPosition.x = -pTr->mPosition.x;
	}
	
	if (pTr->mPosition.y > 1.15f || pTr->mPosition.y < -1.15f)
	{
		pTr->mPosition.y = -pTr->mPosition.y;
	}

}

void WrapDrones(GameObjectInstance* pInst)
{
	Transform* pTr = (Transform*)pInst->GetComponent(COMPONENT_TRANSFORM);

	/*if (pTr->mPosition.x > 1.15f || pTr->mPosition.x < -1.15f)
	{
		pTr->mPosition.x = -pTr->mPosition.x;
	}*/

	if (pTr->mPosition.y > 1.15f || pTr->mPosition.y < -1.15f)
	{
		pTr->mPosition.y = -pTr->mPosition.y;
	}

}
void WrapSkyBox(GameObjectInstance* pInst)
{
	Transform* pTr = (Transform*)pInst->GetComponent(COMPONENT_TRANSFORM);

	if (pTr->mPosition.x > 2.043f || pTr->mPosition.x < -2.043f)
	{
	pTr->mPosition.x = -pTr->mPosition.x;
	}
}

