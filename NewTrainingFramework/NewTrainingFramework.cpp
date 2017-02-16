// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "../Utilities/Model.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include <conio.h>
#include <stdio.h>
#define LIMIT_FPS 60
int Init(ESContext *esContext)
{
	ResourceManager::GetInstance()->Init();
	SceneManager::GetInstance()->Init();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	return 0;
}
void Draw(ESContext *esContext)
{
	glClear(GL_COLOR_BUFFER_BIT);
	SceneManager::GetInstance()->Draw();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}
void Update(ESContext *esContext, float deltaTime)
{
	
}

void Key(ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (key >= 'A' && key <= 'Z'){
		SceneManager::GetInstance()->Move(1.0f / LIMIT_FPS, key);
	}
	else{
		SceneManager::GetInstance()->Rotate(1.0f / LIMIT_FPS, key);
	}
}

void CleanUp()
{
	delete ResourceManager::GetInstance();
	delete SceneManager::GetInstance();
}

int _tmain()
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Hello Objects", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

