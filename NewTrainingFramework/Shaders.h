#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute, uvAttribute, mvpUniform;
	int id;
	Shaders();
	Shaders(int id, char * fileVS, char * fileFS);
	int Init(char *, char *);
	~Shaders();
};