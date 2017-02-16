#pragma once
#include "../Utilities/utilities.h"
#include "../NewTrainingFramework/Vertex.h"
#include "../NewTrainingFramework/Shaders.h"
#include "../NewTrainingFramework/Object.h"
class Texture{
public:
	Texture();
	Texture(int, char *);
	Texture(int, char[6][100]);
	~Texture();
	GLuint textureID;
	int m_id, m_type;
	void Init(char *);
	void InitCube(char location[6][100]);
};