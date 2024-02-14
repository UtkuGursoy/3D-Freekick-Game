#include "GameObject.h"

GameObject::GameObject(): transform()
{
	scale(10);
}

GameObject::GameObject(float x, float y, float z) : transform(x,y,z)
{
	scale(10);
}

GameObject::GameObject(float px, float py, float pz, float rx, float ry, float rz) : transform(px, py, pz, rx, ry, rz)
{
	scale(10);
}

GameObject::GameObject(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz) 
	: transform(px, py, pz, rx, ry, rz, sx, sy, sz)
{
	scale(10);
}


void GameObject::draw()
{
}

void GameObject::scale(float scale)
{
	transform.scale.x *= scale;
	transform.scale.y *= scale;
}

void GameObject::remove() const
{
	delete this;
}
