#pragma once
#include "GameObject.h"

class Wall :
    public GameObject
{
		GLuint m_texture;
	public:
		Wall(GLuint tex);
		Wall(GLuint tex, float x, float y, float z);
		Wall(GLuint tex, float px, float py, float pz, float rx, float ry, float rz);
		Wall(GLuint tex, float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz);
		void draw();
};

