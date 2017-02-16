#pragma once
#include <vector>
#include "Object.h"
#include "Camera.h"
class SceneManager{
private:
	static SceneManager * m_instance;
	std::vector<Object*> m_objectManager;

	SceneManager();
	int m_numObject;
public:
	void Move(float deltaTime,char key);
	void Rotate(float deltaTime, char key);
	void Draw();
	void Init();
	void Update();
	Camera * m_camera;
	Matrix m_per;
	static SceneManager * GetInstance();
	~SceneManager();
};