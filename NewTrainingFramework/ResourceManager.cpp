#include "stdafx.h"
#include "ResourceManager.h"
#include "../NewTrainingFramework/Shaders.h"
#include "../Utilities/Model.h"
#include "../Utilities/Texture.h"
#include <vector>
ResourceManager * ResourceManager::m_instance = NULL;
ResourceManager * ResourceManager::GetInstance() {
	if (m_instance == 0){
		m_instance = new ResourceManager();
	}
	return m_instance;
}
ResourceManager::ResourceManager(){}
void ResourceManager::Init(){
	FILE *file = fopen("../RM.txt", "r");
	if (file == NULL){
		printf("Cant open file!");
		return;
	}
	char directory[100],directory1[100];
	int id;
	char directoryCube[6][100];
	//read models
	fscanf(file, "#MODEL %d\n", &m_numModel);
	for (int i = 0; i < m_numModel; i++){
		fscanf(file, "#ID %d\n", &id);
		fscanf(file, "FILE %s\n", &directory);
		if (i == 0){
			m_modelManager.push_back(new Model(id, directory,1));
		}
		else{
			m_modelManager.push_back(new Model(id, directory));
		}
		//printf("%s\n", directory);
	}

	//read 2d textures
	fscanf(file, "\n#TEXTURE2D %d\n", &m_num2DTexture);
	for (int i = 0; i < m_num2DTexture; i++){
		fscanf(file, "#ID %d\n", &id);
		fscanf(file, "FILE %s\n", &directory);
		m_texture2DManager.push_back(new Texture(id, directory));
		//printf("%s\n", directory);
	}

	//read cube textures
	fscanf(file, "\n#TEXTURECUBE %d\n", &m_numCubeTexture);
	for (int i = 0; i < m_numCubeTexture; i++){
		fscanf(file, "#ID %d\n", &id);
		fscanf(file, "FILERIGHT %s\n", &directoryCube[0]);
		fscanf(file, "FILELEFT %s\n", &directoryCube[1]);
		fscanf(file, "FILEUP %s\n", &directoryCube[2]);
		fscanf(file, "FILEDOWN %s\n", &directoryCube[3]);
		fscanf(file, "FILEFRONT %s\n", &directoryCube[4]);
		fscanf(file, "FILEBACK %s\n", &directoryCube[5]);
		m_cubeTextureManager.push_back(new Texture(id, directoryCube));
		/*for (int i = 0; i < 6; i++){
			printf("%s\n", directoryCube[i]);
		}*/

	}
	

	//read shaders
	fscanf(file, "\n#SHADER %d\n", &m_numShader);
	for (int i = 0; i < m_numShader; i++){
		fscanf(file, "#ID %d\n", &id);
		fscanf(file, "FILEVS %s\n", &directory);
		fscanf(file, "FILEFS %s\n", &directory1);
		m_shaderManager.push_back(new Shaders(id, directory,directory1));
		//printf("%s %s\n", directory,directory1);
	}

	fclose(file);
}
ResourceManager::~ResourceManager(){
	for (int i = 0; i < m_modelManager.size(); i++){
		delete m_modelManager[i];
	}
	for (int i = 0; i < m_shaderManager.size(); i++){
		delete m_shaderManager[i];
	}
	for (int i = 0; i < m_texture2DManager.size(); i++){
		delete m_texture2DManager[i];
	}
	for (int i = 0; i < m_cubeTextureManager.size(); i++){
		delete m_cubeTextureManager[i];
	}
}
Model * ResourceManager::GetModelByID(int id){
	for (int i = 0; i < m_modelManager.size(); i++){
		if (m_modelManager[i]->m_id == id){
			return m_modelManager[i];
		}
	}
}
Texture * ResourceManager::GetTexture2DByID(int id){
	for (int i = 0; i < m_texture2DManager.size(); i++){
		if (m_texture2DManager[i]->m_id == id){
			return m_texture2DManager[i];
		}
	}
}
Texture * ResourceManager::GetTextureCubeByID(int id){
	for (int i = 0; i < m_cubeTextureManager.size(); i++){
		if (m_cubeTextureManager[i]->m_id == id){
			return m_cubeTextureManager[i];
		}
	}
}
Shaders * ResourceManager::GetShaderByID(int id){
	for (int i = 0; i < m_shaderManager.size(); i++){
		if (m_shaderManager[i]->id == id){
			return m_shaderManager[i];
		}
	}
}
