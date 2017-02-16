#pragma once
#include "../Utilities/utilities.h"
#include "Texture.h"
#include "../NewTrainingFramework/Shaders.h"
#include "../NewTrainingFramework/Object.h"
class Model{
public:
	GLuint m_vboId, m_iboID, m_modelID;
	int  m_nVertice, m_nIndex, m_id;
	void Init(char *filename,int type = 0);
	Model();
	Model(int id,char *filename,int type = 0);
	~Model();
};