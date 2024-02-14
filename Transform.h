#pragma once
#include "Vector3.h"

class Transform { // Contains all translational data for the object.
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Transform();
	Transform(float x, float y, float z);
	Transform(float px, float py, float pz, float rx, float ry, float rz);
	Transform(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz);
	
};
