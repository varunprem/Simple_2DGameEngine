#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <unordered_map>
#include "GameObjectInstance.h"
//#include "SDL_mixer.h"
struct SDL_Surface;

class ResourceManager{

public:
	ResourceManager();
	~ResourceManager();

	SDL_Surface *GetSurfaces(char* path);
	unsigned char *GetTexture(char* path, int &width, int &height, int &channels);
	void LoadSurfaces();
	void UpdateScreenSurface(SDL_Window* pWindow, SDL_Surface* pSurfaces);
//	Mix_Music* GetMusic(char* filePath);
//	Mix_Chunk* GetSFX(char* filePath);
public:
	std::unordered_map<std::string, unsigned char*>mTexture;    // load textures 

	std::unordered_map<std::string, SDL_Surface* >mSurfaces;    // load SDL textures for screen menu
	
//	std::unordered_map<std::string, Mix_Music*> mMusic;   // background music
//	std::unordered_map<std::string, Mix_Chunk*> mSFX;    // sound effects 
	SDL_Surface* ImageSet[4] = { NULL, NULL,NULL,NULL};
};



#endif