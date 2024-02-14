#pragma once
#include "TexturedPlane.h"
class Target :
    public TexturedPlane
{
private:
	int m_score;
	GLuint m_originalTexture;
	bool m_hit;
public:
	Target(GLuint tex, int score);
	Target(GLuint tex, int score, float r);
	Target(GLuint tex, int score, float r, float x, float y, float z);
	Target(GLuint tex, int score, float r, float px, float py, float pz, float rx, float ry, float rz);
	int getScore() const;
	bool Target::isHit() const;
	void hit(GLuint newTexture);
	void reset();
};

