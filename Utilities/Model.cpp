#include "stdafx.h"
#include "Model.h"
#include <stdio.h>
#include "../NewTrainingFramework/Vertex.h"
#include "../NewTrainingFramework/Shaders.h"
#include <stdlib.h>     
#include <time.h>     
void Model::Init(char *fileNFG,int type){
	srand(time(NULL));
	int id;
	int m_type;
	Vertex *verticesData;
	GLuint *index;
	FILE *file = fopen(fileNFG, "r");
	if (file == NULL){
		printf("Cant open file!");
		return;
	}
	fscanf(file, "NrVertices:%d\n", &m_nVertice);
	verticesData = new Vertex[m_nVertice];
	for (int i = 0; i < m_nVertice; i++){
		/*
		0. pos:[0.134000, 1.020300, -0.083900]; norm:[0.662725, 0.317712, -0.678126]; binorm:[0.014559, 0.899903, 0.435847]; tgt:[-0.748721, 0.298719, -0.591763]; uv:[0.611900, 0.886700];
		*/
		fscanf(file, "%d. ", &id);
		fscanf(file, "pos:[%f, %f, %f]; ", &verticesData[i].pos.x, &verticesData[i].pos.y, &verticesData[i].pos.z);
		fscanf(file, "norm:[%f, %f, %f]; ", &verticesData[i].normal.x, &verticesData[i].normal.y, &verticesData[i].normal.z);
		fscanf(file, "binorm:[%f, %f, %f]; ", &verticesData[i].binormal.x, &verticesData[i].binormal.y, &verticesData[i].binormal.z);
		fscanf(file, "tgt:[%f, %f, %f]; ", &verticesData[i].tangent.x, &verticesData[i].tangent.y, &verticesData[i].tangent.z);
		fscanf(file, "uv:[%f, %f];\n", &verticesData[i].uv.x, &verticesData[i].uv.y);
		//printf("%d: pos: %f %f %f, uv: %f %f\n", id, verticesData[i].pos.x, verticesData[i].pos.y, verticesData[i].pos.z, verticesData[i].uv.x, verticesData[i].uv.x);

		//modify height if model is terrain
		if (type == 1){
			verticesData[i].pos.y = ((float)rand() / (float)(RAND_MAX)) * 1.5f - 1;
		}
	}
	fscanf(file, "NrIndices:%d\n", &m_nIndex);
	index = new GLuint[m_nIndex];
	//printf("%d\n", m_nIndex);
	for (int i = 0; i < m_nIndex; i += 3){
		/*
		0.    0,    1,    2
		*/
		fscanf(file, "%d.", &id);
		fscanf(file, "%u, %u, %u\n", index + i, index + i + 1, index + i + 2);
		//printf("%d: %u %u %u\n", id, index[i], index[i + 1], index[i + 2]);
	}
	fclose(file);
	glGenBuffers(1, &m_vboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_nVertice, verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//buffer index
	glGenBuffers(1, &m_iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_nIndex, index, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//free momory
	delete[] verticesData;
	delete[] index;
}
Model::~Model(){
	glDeleteBuffers(1, &m_vboId);
	glDeleteBuffers(1, &m_iboID);
}
Model::Model(int id, char * fileNFG,int type) : m_id(id){
	Init(fileNFG,type);
}
Model::Model(){
	
}