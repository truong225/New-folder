#include "stdafx.h"
#include "../Utilities/utilities.h" 
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "../Utilities/Model.h"
#include "SceneManager.h"
#include <stdio.h>
void Object::SetMatrix(Matrix s, Matrix r, Matrix t){
	m_worldMatrix = s * r * t;
}
Object::Object(Model * model, std::vector<class Texture*> texture, Shaders * shader, Matrix m_scale, Matrix rotate, Matrix position) : m_angle(0.0f), m_model(model), m_texture2D(texture), m_shader(shader), m_scale(m_scale), m_rotation(rotate), m_transform(position){}
Object::Object(){};
Object::~Object(){}
void Object::Update(){
	m_worldMatrix = m_scale * m_rotation * m_transform * SceneManager::GetInstance()->m_camera->m_viewMat * SceneManager::GetInstance()->m_per;
}
void Object::Spin(){
	m_rotation.SetRotationAngleAxis(m_angle,0,1,1);
	m_angle = m_angle + .05;
	m_worldMatrix = m_scale * m_rotation * m_transform;
}
void Object::Draw(){

	glUseProgram(m_shader->program);
	glEnable(GL_DEPTH_TEST);
	//bind vbo and ibo buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_model->m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->m_iboID);
	int iTextureLoc[20];

	//bind texture buffer based on type of texture
	if (m_texture2D[0]->m_type == 1) {	//texture 2D
		for (int i = 0; i < m_texture2D.size(); i++){
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_texture2D[i]->textureID);

			//initialize texture name in the fragment shader
			char * t = "u_texture";
			int len = strlen(t);
			char * nameTexture = new char[15];
			strcpy(nameTexture, t);
			nameTexture[len] = (char)(i + '0');
			nameTexture[len + 1] = '\0';
			
			//get location
			iTextureLoc[i] = glGetUniformLocation(m_shader->program, nameTexture);
			glUniform1i(iTextureLoc[i], i);

			//free memory
			delete[] nameTexture;
		}
	}
	else{ // texture cube
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture2D[0]->textureID);
		int iTextureLoc = glGetUniformLocation(m_shader->program, "u_texture");
		glUniform1i(iTextureLoc, 0);
	}
	 
	int matrixLoc = glGetUniformLocation(m_shader->program, "u_mvp");
	glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, (GLfloat *)m_worldMatrix.m);

	if (m_shader->positionAttribute != -1){
		glEnableVertexAttribArray(m_shader->positionAttribute);
		glVertexAttribPointer(m_shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (m_shader->uvAttribute != -1){
		glEnableVertexAttribArray(m_shader->uvAttribute);
		glVertexAttribPointer(m_shader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3)* 4));
	}

	glDrawElements(GL_TRIANGLES, m_model->m_nIndex, GL_UNSIGNED_INT, 0);

	//unbind vbo and ibo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//unbind texture
	if (m_texture2D[0]->m_type == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}