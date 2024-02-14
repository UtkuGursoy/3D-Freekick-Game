#include "Transform.h"

Transform::Transform() : position(0,0,0), rotation(0, 0, 0), scale(1, 1, 1)
{
}

Transform::Transform(float x, float y, float z): position(x, y, z), rotation(0, 0, 0), scale(1, 1, 1)
{
}


Transform::Transform(float px, float py, float pz, float rx, float ry, float rz) : position(px, py, pz), rotation(rx, ry, rz), scale(1, 1, 1)
{
}

Transform::Transform(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz)
	: position(px, py, pz), rotation(rx, ry, rz), scale(sx, sy, sz)
{
}