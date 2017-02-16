#include "stdafx.h"
#include "Texture.h"
Texture::Texture(){

}
Texture::Texture(int id, char * fileTGA) : m_id(id){
	Init(fileTGA);
}
Texture::Texture(int id, char fileTGA[6][100]) : m_id(id){
	InitCube(fileTGA);
}
Texture::~Texture(){
	glDeleteTextures(1, &textureID);
}
void Texture::Init(char *filename){
	glGenTextures(1, &textureID);
	m_type = 1;
	//bind and load data
	int w, h, bpp;
	glBindTexture(GL_TEXTURE_2D, textureID);
	char *imageData = LoadTGA(filename, &w, &h, &bpp);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

	//setting texture paramaters
	//wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	//free memory
	delete[] imageData;
}
void Texture::InitCube(char location[6][100]){
	//generate ID and type
	glGenTextures(1, &textureID);
	m_type = 2;

	//bind texture
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	//init array
	int w, h, bpp;
	char *imageData;

	//load data
	for (int i = 0; i < 6; i++){
		imageData = LoadTGA(location[i], &w, &h, &bpp);
		glTexImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,			0,			GL_RGB,			w,			h,			0,			GL_RGB,			GL_UNSIGNED_BYTE,			imageData);
		delete[] imageData;
	}
	
	//setting texture paramaters
	//wrap
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//filters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//unbind
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

}