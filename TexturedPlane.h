#pragma once
#include "GameObject.h"
class TexturedPlane :
    public GameObject
{
public:
	GLuint m_texture;
	TexturedPlane(GLuint tex);
	TexturedPlane(GLuint tex, float x, float y, float z);
	TexturedPlane(GLuint tex, float px, float py, float pz, float rx, float ry, float rz);
	TexturedPlane(GLuint tex, float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz);
	void draw();
};

