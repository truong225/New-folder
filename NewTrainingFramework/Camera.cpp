#include "stdafx.h"
#include "Camera.h"
Camera::Camera(){}
Camera::~Camera(){}
void Camera::Init(){}
void Camera::Move(float deltaTime,char key){
	//Configure camera to move 
	Vector3 deltaMove, OY;
	switch (key){
	case 'W':
		printf("Forward\n");
		deltaMove = -(m_position - m_target).Normalize() * deltaTime * m_speed;
		break;
	case 'S':
		printf("Backward\n");
		deltaMove = (m_position - m_target).Normalize() * deltaTime * m_speed;
		break;
	case 'D':
		printf("Right\n");
		OY = Vector3(0, 1.0f, 0);
		deltaMove = OY.Cross(m_position - m_target).Normalize() * deltaTime * m_speed;
		break;
	case 'A':
		printf("Left\n");
		OY = Vector3(0, 1.0f, 0);
		deltaMove = -OY.Cross(m_position - m_target).Normalize() * deltaTime * m_speed;
		break;
	}
	m_position += deltaMove;
	m_target += deltaMove;
	Calculate();
}
void Camera::Rotate(float deltaTime, char key){
	Vector4 newTarget = Vector4(0, 0, -(m_position - m_target).Length(), 1);
	Matrix rotate;
	switch (key){
	case 0x25:
		printf("Turn left\n");
		rotate.SetRotationY(deltaTime * m_speed);
		break;
	case 0x26:
		printf("Turn up\n");
		rotate.SetRotationX(deltaTime * m_speed);
		break;
	case 0x27:
		printf("Turn right\n");
		rotate.SetRotationY(-deltaTime * m_speed);
		break;
	case 0x28:
		printf("Turn down\n");
		rotate.SetRotationX(-deltaTime * m_speed);
		break;
	}
	newTarget = newTarget * rotate;
	newTarget = newTarget * m_worldMat;
	m_target.x = newTarget.x;
	m_target.y = newTarget.y;
	m_target.z = newTarget.z;
	Calculate();
}
void Camera::Calculate(){
	Vector3 xaxis, yaxis, zaxis;
	Matrix r, t, reverT;

	//calcualte rotate matrix
	zaxis = (m_position - m_target).Normalize();
	xaxis = (m_up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();
	r.m[0][0] = xaxis.x; r.m[0][1] = xaxis.y; r.m[0][2] = xaxis.z; r.m[0][3] = 0.0f;
	r.m[1][0] = yaxis.x; r.m[1][1] = yaxis.y; r.m[1][2] = yaxis.z; r.m[1][3] = 0.0f;
	r.m[2][0] = zaxis.x; r.m[2][1] = zaxis.y; r.m[2][2] = zaxis.z; r.m[2][3] = 0.0f;
	r.m[3][0] = 0.0f; r.m[3][1] = 0.0f; r.m[3][2] = 0.0f; r.m[3][3] = 1.0f;

	//and other matrices
	t.SetTranslation(m_position.x, m_position.y, m_position.z);
	reverT.SetTranslation(-m_position.x, -m_position.y, -m_position.z);

	m_worldMat = r * t;
	m_viewMat = reverT * r.Transpose();
}
Camera::Camera(Vector3 position, Vector3 target, Vector3 up) : m_position(position), m_target(target), m_up(up), m_speed(1.0f){
	Calculate();
}