#pragma once
#include "stdafx.h"
#include "SceneManager.h"
#include "Vertex.h"
#include "Object.h"
#include "ResourceManager.h"
SceneManager * SceneManager::m_instance = NULL;
SceneManager * SceneManager::GetInstance(){
	if (m_instance == 0){
		m_instance = new SceneManager();
	}
	return m_instance;
}
SceneManager::SceneManager(){}
void SceneManager::Init(){
	//some temporary variables
	int id, modelID, tex2count, tex3count, shaderID;
	int texture2dID, textureCubeID;
	Matrix rotate, position, scale;
	std::vector<class Texture*> textureLoc;
	Vector3 coordinate,pos, tar,up;
	float angle;

	//set up matrix perspective(temporary)
	m_per.SetPerspective(1, 4.0f / 3.0f, 0.1f, 100.0f);

	//open file
	FILE *file = fopen("../SM.txt", "r");
	if (file == NULL){
		printf("Cant open file!");
		return;
	}

	//read and load camera from file
	fscanf(file, "#CAMERA\n");
	fscanf(file, "#POSITION (%f, %f, %f)\n", &pos.x, &pos.y, &pos.z);
	fscanf(file, "#TARGET (%f, %f, %f)\n", &tar.x, &tar.y, &tar.z);
	fscanf(file, "#UP (%f, %f, %f)\n", &up.x, &up.y, &up.z);
	m_camera = new Camera(pos, tar, up);

	//read and load object from file
	fscanf(file, "#OBJECT %d\n", &m_numObject);
	
	for (int i = 0; i < m_numObject; i++){
		textureLoc.clear();
		fscanf(file, "#ID %d\n", &id);
		fscanf(file, "#MODELID %d\n", &modelID);
		fscanf(file, "#TEXTURE2DCOUNT %d\n", &tex2count);
		for (int j = 0; j < tex2count; j++){
			fscanf(file, "#TEXTURE2DID %d\n", &texture2dID);
			textureLoc.push_back(ResourceManager::GetInstance()->GetTexture2DByID(texture2dID));
		}
		fscanf(file, "#TEXTURECUBECOUNT %d\n", &tex3count);
		for (int j = 0; j < tex3count; j++){
			fscanf(file, "#TEXTURECUBEID %d\n", &textureCubeID);
			textureLoc.push_back(ResourceManager::GetInstance()->GetTextureCubeByID(textureCubeID));
		}
		fscanf(file, "#SHADERID %d\n", &shaderID);
		fscanf(file, "#SCALE (%f, %f, %f)\n", &coordinate.x, &coordinate.y, &coordinate.z);
		scale.SetScale(coordinate);
		fscanf(file, "#ROTATION (%f ,%f, %f, %f)\n", &angle, &coordinate.x, &coordinate.y, &coordinate.z);
		rotate.SetRotationAngleAxis(angle, coordinate.x, coordinate.y, coordinate.z);
		fscanf(file, "#POSITION (%f, %f, %f)\n", &coordinate.x, &coordinate.y, &coordinate.z);
		position.SetTranslation(coordinate);
		Object * o = new Object(ResourceManager::GetInstance()->GetModelByID(modelID),
								textureLoc,
								ResourceManager::GetInstance()->GetShaderByID(shaderID),
								scale, rotate, position);
		o->Update();
		m_objectManager.push_back(o);
	}

	//close file
	fclose(file);
}
SceneManager::~SceneManager(){
	for (int i = 0; i < m_objectManager.size(); i++){
		delete m_objectManager[i];
	}
	delete m_camera;
}
void SceneManager::Draw(){
	for (int i = 0; i < m_objectManager.size(); i++){
		m_objectManager[i]->Draw();
	}
}
void SceneManager::Update(){
	for (int i = 0; i < m_objectManager.size(); i++){
		m_objectManager[i]->Spin();
	}
}
void SceneManager::Move(float deltaTime,char key){
	m_camera->Move(deltaTime,key);
	for (int i = 0; i < m_objectManager.size(); i++){
		m_objectManager[i]->Update();
	}
}
void SceneManager::Rotate(float deltaTime, char key){
	m_camera->Rotate(deltaTime, key);
	for (int i = 0; i < m_objectManager.size(); i++){
		m_objectManager[i]->Update();
	}
}