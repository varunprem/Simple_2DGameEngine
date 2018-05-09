#include "MeshInstance.h"
#include <windows.h>


#include <iostream>
#include <fstream>
#include <string>


using namespace std;


// GLEW
#define GLEW_STATIC
#include <glew.h>

// GLFW
#include <glfw3.h>
#include "Shader.h"
#include "MeshInstance.h"
#include "matrix.h"
#include <stdlib.h>
#include <string>

using namespace std;


MeshInstance::MeshInstance() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

}


void MeshInstance::DrawMeshTriangle() {

	this->LoadMeshTriangle();
	
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);


}


void MeshInstance::LoadMeshTriangle() {


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//For position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//For Colour
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


}


void MeshInstance::LoadMeshRectangle() {

	GLuint indices[] = {
		0,1,3,
		1,2,3
	};

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);\

	//For Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//For Colour
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO


	// Uncommenting this call will result in wireframe polygons.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


}


void MeshInstance::DrawMeshRectangle()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}


void MeshInstance::Serialize(char* filePath)
{
	FILE* fpInput;
	int tcols, trows = 0;
	char buffer[255];
	static float **MapData;

	fpInput = fopen(filePath, "r");

	if (!fpInput)
	{
		printf("Unable to open the file");
		return;

	}

	//Retrieve the rows and cols
	for (int i = 0; i<4; i++)
	{

		fscanf(fpInput, "%s", buffer);

		if (i == 1) {
			tcols = atoi(buffer);


		}
		if (i == 3) {
			trows = atoi(buffer);

		}


	}

	printf("Rows: %d, Cols: %d\n", trows, tcols);

	
	//cout << "Inside vertices" << endl;
	for (int rows = 0 ; rows < trows ; rows++)
	{
		for (int cols = 0; cols < tcols; cols++)
		{
			fscanf(fpInput, "%s", buffer);

			vertices[rows * tcols + cols] = atof(buffer);

			
		}
		

	}

	//for (int i = 0; i < 24; i++)
	//{
	//	cout << vertices[i] << "\t";
	//}

	
}


MeshInstance::~MeshInstance() {

	//Clearing up the VAO and VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//Clearing up the stored vertices
	/*for (int i = 0; i < MAX_VERTICES; i++)
	{
		vertices[i] = 0;
	}*/
}