#pragma once
#include "../Utilities/utilities.h"
#include "../NewTrainingFramework/Vertex.h"
#include "../NewTrainingFramework/Shaders.h"
#include "../Utilities/Model.h"
#include <vector>
class Object{
public:
	int m_id;
	Matrix m_rotation, m_scale, m_transform, m_worldMatrix;
	float m_angle;
	class Model * m_model;
	std::vector<class Texture*> m_texture2D;
	class Shaders * m_shader;
	void Update();
	void SetMatrix(Matrix, Matrix, Matrix);
	void Draw();
	void Spin();
	Object();
	Object(Model * model, std::vector<class Texture*> texture, Shaders * shader, Matrix scale, Matrix rotate, Matrix position);
	~Object();
};