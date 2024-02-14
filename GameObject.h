#pragma once
#include <gl/freeglut.h>
#include "Transform.h"
class GameObject //Base class for every object, used to store position and size information.
{
public:
	Transform transform; // Transform holds position, scale and rotational information.
	GameObject();
	GameObject(float x, float y, float z);
	GameObject(float px, float py, float pz, float rx, float ry, float rz);
	GameObject(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz);
	void draw();
	void scale(float);
	void remove() const;
};

