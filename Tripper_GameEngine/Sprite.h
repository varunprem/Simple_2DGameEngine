#ifndef SPRITE_H
#define SPRITE_H
#include <stdio.h>
//#include <SDL.h>
#include "Component.h"
#include <string>
#include "GameObjectInstance.h"
//#include "ResourceManager.h"
#include "EventManager.h"
#include "Shader.h"
#include <windows.h>
#include <iostream>
#include <stdio.h>

#include <GL/glew.h>
#include <gl/gl.h>
#include "matrix.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#define MAX_VERTICES 32

enum ShapeType 
{
	DAN,
	BULLET,
	DRONES,
	KILLSHOT,
	GUNSHIP,
	BULLETFIRE,
	SKYBOX_SCROLL,
	SENTINEL_BULLET,
	RANGE_DRONES,
	HEALTHBAR,

	NUM
};

class GameObjectInstance;

class Sprite: public Component
{

public:
	Sprite():Component(COMPONENT_SPRITE)
	{
		//mSurface = NULL;
	}
	
	~Sprite();

	//void AddSprite(SDL_Surface* surface);
	
	
	void Update();

	 void Serialize(FILE** fpp);

	 void SerializeVertices(char* filePath);

	 void DrawMesh(Shader pShader);
	 void drawText(const char *text, int length, int x, int y);
	 void LoadMesh(char* spriteName);
	 char* GetSpriteName();
	 void SetSpriteName(char* SpriteName) 
	 {
		 pSpriteName = SpriteName;
	 }
	 //void LoadSprite(char* path);
	 void HandleEvent(Event* ev);
	

public:
	//SDL_Surface* mSurface;
	GLuint VAO, VBO, EBO;
	GLfloat vertices[MAX_VERTICES];

	unsigned int mType;
	unsigned int texture1;
	bool active;
	char *pSpriteName;
	GameObjectInstance* droneTarget;
	unsigned char *textData;
	int width, height , channels;
	char spriteName[256];
};



#endif