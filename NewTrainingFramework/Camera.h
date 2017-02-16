#pragma once
#include "../Utilities/utilities.h"
#include "../NewTrainingFramework/Vertex.h"
#include "../NewTrainingFramework/Shaders.h"
#include "../Utilities/Model.h"
#include "Vertex.h"
#include <vector>
class Camera{
public:
	Vector3 m_position, m_target, m_up;
	Matrix m_viewMat, m_worldMat;
	float m_speed;
	void Init();
	void Move(float deltaTime,char key);
	void Rotate(float deltaTime, char key);
	void Calculate();
	Camera(Vector3 position, Vector3 target,Vector3 up);
	Camera();
	~Camera();
};