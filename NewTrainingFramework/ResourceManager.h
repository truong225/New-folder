#pragma once
#include "../NewTrainingFramework/Shaders.h"
#include "../Utilities/Model.h"
#include "../Utilities/Texture.h"
#include <vector>
class ResourceManager{
private:
	static ResourceManager * m_instance;
	ResourceManager();
	int m_numModel, m_num2DTexture, m_numCubeTexture, m_numShader;
public:
	std::vector<Model*> m_modelManager;
	std::vector<Texture*> m_texture2DManager;
	std::vector<Texture*> m_cubeTextureManager;
	std::vector<Shaders*> m_shaderManager;
	void Init();
	Model * GetModelByID(int id);
	Texture * GetTexture2DByID(int id);
	Texture * GetTextureCubeByID(int id);
	Shaders * GetShaderByID(int id);
	static ResourceManager * GetInstance();
	~ResourceManager();
};