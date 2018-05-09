#include "ResourceManager.h"
#include "SDL_surface.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <iostream>
extern bool _gameIsOn;
extern bool _controlScreen;
extern bool _gameControl;
extern bool _gameWin;
//#ifndef STBI_INCLUDE
//#define STBI_INCLUDE
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//#endif // !STBI_INCLUDE

ResourceManager::ResourceManager()
{

}
ResourceManager::~ResourceManager()
{
	for(auto &i : mSurfaces)
		SDL_FreeSurface(i.second);

	mSurfaces.clear();
}
SDL_Surface* ResourceManager:: GetSurfaces(char* path)
{
	SDL_Surface* pSurfaces = mSurfaces[path];

	//Found
	if(pSurfaces!= NULL)
		return pSurfaces;
	//Not Found
	pSurfaces = SDL_LoadBMP(path);

	if(pSurfaces != NULL)
		mSurfaces[path] = pSurfaces;

	return pSurfaces;

}
void ResourceManager::LoadSurfaces()
{
	ImageSet[0] = GetSurfaces("..\\Resources\\SplashScreen.bmp");
	if (NULL == ImageSet[0])
		printf("Null Image 0");
	ImageSet[1] = GetSurfaces("..\\Resources\\ControlsScreen.bmp");
	if (NULL == ImageSet[1])
		printf("Null Image 1");
	ImageSet[2] = GetSurfaces("..\\Resources\\MissionSuccessful.bmp");
	if (NULL == ImageSet[2])
		printf("Null Image 2");
	ImageSet[3] = GetSurfaces("..\\Resources\\MissionFailure.bmp");
	if (NULL == ImageSet[3])
		printf("Null Image 3");
}
void ResourceManager::UpdateScreenSurface(SDL_Window* pWindow, SDL_Surface* pSurfaces)
{
	if (_gameWin)
	{
		SDL_BlitSurface(ImageSet[2], NULL, pSurfaces, NULL);
		SDL_UpdateWindowSurface(pWindow);
	}
	else if (_gameControl == false)
	{
		SDL_BlitSurface(ImageSet[3], NULL, pSurfaces, NULL);
		SDL_UpdateWindowSurface(pWindow);
	}
	
	else if(_controlScreen)
	{
		SDL_BlitSurface(ImageSet[1], NULL, pSurfaces, NULL);
		SDL_UpdateWindowSurface(pWindow);
	}
	else if (_gameIsOn == false)
	{
		SDL_BlitSurface(ImageSet[0], NULL, pSurfaces, NULL);
		SDL_UpdateWindowSurface(pWindow);
	}
}
//Mix_Music * ResourceManager::GetMusic(char* filePath)
//{
//	Mix_Music* pMusic = mMusic[filePath];
//
//	if (pMusic!= NULL)
//		return pMusic;
//	pMusic = Mix_LoadMUS(filePath);
//	if (pMusic == NULL)
//		printf("Unable to load backgroud Music");
//
//	if (pMusic != NULL)
//		mMusic[filePath] = pMusic;
//
//	return pMusic;
//}
//Mix_Chunk * ResourceManager::GetSFX(char* filePath)
//{
//	Mix_Chunk* pSFX = mSFX[filePath];
//
//	if (pSFX != NULL)
//		return pSFX;
//	pSFX = Mix_LoadWAV(filePath);
//	if (pSFX == NULL)
//		printf("Unable to load backgroud Music");
//
//	if (pSFX != NULL)
//		mSFX[filePath] = pSFX;
//
//	return pSFX;
//}

unsigned char * ResourceManager::GetTexture(char * path, int &width, int &height, int &channels)
{
	// load image, create texture and generate mipmaps
	
	//stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
											// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	auto it = mTexture.find(path);

	if(it==mTexture.end())
	{
	// unsigned char *data = stbi_load(path, &width, &height, &channels, 0);
	// mTexture[path] = data;
	}
	
	return  mTexture[path];
}




