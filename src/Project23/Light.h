#pragma once
#include <GL/glut.h>
#include "Vector3f.h"
#include "Vector4f.h"

class Light
{
public:
	Light(int x, int y, int z, int L_ID);
	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);

	int getID();

	void draw() const;

private:
	int lightID;
	Vector3f pos;
	Vector4f ambient;
	Vector4f diffuse;
	Vector4f specular;
};
