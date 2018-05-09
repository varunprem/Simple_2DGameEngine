#pragma once

#ifndef GRAPHICS_MANAGER_H
#define GRAPHICS_MANAGER_H

#include <windows.h>
#include <iostream>
#include <stdio.h>

#include <GL/glew.h>
#include <gl/gl.h>
#include "matrix.h"



#define MAX_VERTICES 500




class MeshInstance {

public:
	MeshInstance();
	void Serialize(char* filePath);

	//To draw a triangle
	void DrawMeshTriangle();
	void LoadMeshTriangle();

	//To draw a rectangle
	void LoadMeshRectangle();
	void DrawMeshRectangle();

	

	

	~MeshInstance();

public:
	GLuint VAO, VBO, EBO;
	GLfloat vertices[MAX_VERTICES];
	
};




#endif // !GRAPHICS_MANAGER_H

