#include "Sprite.h"
#include "Vector2D.h"
#include "FrameRateController.h"
#include "GameObjectManager.h"
#include "ResourceManager.h"



	#ifndef STBI_INCLUDE
	#define STBI_INCLUDE
	#define STB_IMAGE_IMPLEMENTATION
	#include "stb_image.h"
	#endif // !STBI_INCLUDE


extern EventManager* gpEventManager;
extern FrameRateController* pF;
extern GameObjectManager* gOM;
extern GameObjectInstance* DanJones;
extern ResourceManager* rm;

#define KILLSHOT_ROTATION_SPEED	0.1f
#define KILLSHOT_SPEED       0.6f
Sprite::~Sprite()
{
	//Clearing up the VAO and VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

}

void Sprite::HandleEvent(Event* ev)
{
	if (ev->mType == EVENT_TYPE::DRONE_HIT)
	{
		droneTarget = NULL;
	}
}
void Sprite::Serialize(FILE** fpp)
{
	char spriteFileName[256];
	memset(spriteFileName, 0, 256 * sizeof(char));
	//Reading file location and storing them in the component
	fscanf(*fpp, "%s",spriteFileName);
	textData = rm->GetTexture(spriteFileName ,width, height, channels);
}

void Sprite::DrawMesh(Shader pShader) 
{
//	this->LoadMesh();

//Passing values to the shader
	GLuint transformLoc = glGetUniformLocation(pShader.Program, "transform");
	Transform *pTransform = static_cast<Transform*>(mpOwner->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(pTransform->mpTransform));


	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glBindVertexArray(VAO);
	if (gpEventManager->drawDebug && strstr(spriteName,"NightSky")==0)
	{
		glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);
	}
	else
	
	 {
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	}

	
		
	glBindVertexArray(0);
}

void Sprite::drawText(const char * text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++)
	{
		//glBitmapCharacter(GL_BITMAP)
	}
}

void Sprite::LoadMesh(char* stringName) 
{

	/*float vertices[] = {
		// positions          // colors           // texture coords
		0.1f,  0.1f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		0.1f, -0.1f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.1f, -0.1f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.1f,  0.1f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};*/

	unsigned int indices[] = {
		0, 1, 2, // first triangle
		2, 3, 0 // second triangle
	};


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	active = false;

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//For position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//For Colour
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//For texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	unsigned char *textData = stbi_load(stringName, &width, &height, &channels, 0);

	glPixelStorei(GL_UNPACK_ALIGNMENT, channels);

	if (textData)
	{
		if (channels == 4) {

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textData);
		}
		else {

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textData);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(textData);


	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
void Sprite::Update()
{
	
	if (mType == KILLSHOT)
	{
		GameObjectInstance* killShotMissile;
		killShotMissile = mpOwner;
		GameObjectInstance * mTarget = NULL;
		//Acquiring the target

		//Get the drone Object
		for (GameObjectInstance* pObj : gOM->mGameObjects)
		{
			for (auto i : pObj->mComponents)
			{
				Sprite* pSprite = (Sprite *)pObj->GetComponent(COMPONENT_SPRITE);

				if (pSprite->mType == DRONES)
				{
					if (pSprite->active)
					{
						if (droneTarget == NULL)
						{
							float minimumDistance;
							int flag = 0;

							GameObjectInstance* killShotInst;
							killShotInst = pSprite->mpOwner;

							//Get killshot and drone transform
							Transform* pKillShotTransform = (Transform *)killShotMissile->GetComponent(COMPONENT_TRANSFORM);
							Transform* pDroneTransform = (Transform *)killShotInst->GetComponent(COMPONENT_TRANSFORM);

							if (!flag)
							{
								flag = 1;
								minimumDistance = Vector2DDistance(&pKillShotTransform->mPosition, &pDroneTransform->mPosition);
								if (minimumDistance > 10)
								{
									return;
								}

								else
								{
									mTarget = killShotInst;
								}


							}
							else if (Vector2DDistance(&pKillShotTransform->mPosition, &pDroneTransform->mPosition) < minimumDistance)
							{
								minimumDistance = Vector2DDistance(&pKillShotTransform->mPosition, &pDroneTransform->mPosition);
								if (minimumDistance > 10)
								{
									return;
								}
								else
								{
									mTarget = killShotInst;
								}
							}

							if (flag)
							{
								droneTarget = mTarget;
							}

						}

						//If there is target
						else //if(target != NULL)
						{
							if (pSprite->active)
							{
								Vector2D killShotVelocity;
								Vector2D normalVect;    // normal mapped to generate dot product onto the target
								float dotProduct;

								Body* killShotBody = (Body *)killShotMissile->GetComponent(COMPONENT_BODY);


								Vector2DSet(&normalVect, -killShotBody->VelY, killShotBody->VelX);     // computing normal vector by setting the x value as -y and y value as x

								Transform* pTarget = (Transform *)droneTarget->GetComponent(COMPONENT_TRANSFORM);
								Transform* pKillShotTransform = (Transform *)killShotMissile->GetComponent(COMPONENT_TRANSFORM);

								Vector2DSub(&killShotVelocity, &pTarget->mPosition, &pKillShotTransform->mPosition);

								dotProduct = Vector2DDotProduct(&killShotVelocity, &normalVect);

								Vector2D tempVelocity;    // current velocity of Kill Shot

								tempVelocity.x = killShotBody->VelX;
								tempVelocity.y = killShotBody->VelY;

								if (dotProduct < 0)
								{
									pKillShotTransform->mAngle -= KILLSHOT_ROTATION_SPEED * pF->GetFrameTime();
								}
								else
								{
									pKillShotTransform->mAngle += KILLSHOT_ROTATION_SPEED  * pF->GetFrameTime();
								}

								tempVelocity.x = cosf((pKillShotTransform->mAngle)* 3.14 / 180);
								tempVelocity.y = sinf((pKillShotTransform->mAngle)* 3.14 / 180);

								tempVelocity.x *= KILLSHOT_SPEED;
								tempVelocity.y *= KILLSHOT_SPEED;

								killShotBody->VelX = tempVelocity.x;
								killShotBody->VelY = tempVelocity.y;

							}
						}
					}
				}
			}
		}
	}
}
char* Sprite::GetSpriteName()
{
	 return pSpriteName;
}
void Sprite::SerializeVertices(char* filePath)
{
	FILE* fpInput;
	int tcols, trows = 0;
	char buffer[255];
	//char spriteName[256];
	//static float **MapData;

	fpInput = fopen(filePath, "r");

	if (!fpInput)
	{
		printf("Unable to open the file");
		return;
	}
	fscanf(fpInput, "%s\n", spriteName);
	//Retrieve the rows and cols
	for (int i = 0; i<4; i++)
	{
		fscanf(fpInput, "%s", buffer);

		if (i == 1) 
		{
			tcols = atoi(buffer);
		}
		if (i == 3) 
		{
			trows = atoi(buffer);
		}
	}

	printf("Rows: %d, Cols: %d\n", trows, tcols);

	//cout << "Inside vertices" << endl;
	for (int rows = 0; rows < trows; rows++)
	{
		for (int cols = 0; cols < tcols; cols++)
		{
			fscanf(fpInput, "%s", buffer);

			vertices[rows * tcols + cols] = atof(buffer);


		}
	}

	Serialize(&fpInput);
	LoadMesh(spriteName);
}


 

