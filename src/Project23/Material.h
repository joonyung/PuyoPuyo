#pragma once
#include "Vector4f.h"

class Material
{
public:
	Material();
	void setEmission(float r, float g, float b, float a);
	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	void setEmission(const Vector4f& v);
	void setAmbient(const Vector4f& v);
	void setDiffuse(const Vector4f& v);
	void setSpecular(const Vector4f& v);
	void setShininess(float sh);
	void setColor(int col);

	Vector4f getEmission() const;
	Vector4f getAmbient() const;
	Vector4f getDiffuse() const;
	Vector4f getSpecular() const;
	float getShininess() const;
	int getColor() const;

protected:
	Vector4f emission;
	Vector4f ambient;
	Vector4f diffuse;
	Vector4f specular;
	float shininess;
	int color;
};

