#pragma once
#include <GL/glut.h>
#include "Shape3D.h"
#include "Material.h"

class Sphere : public Shape3D, public Material {
public:
	Sphere();
	Sphere(const Sphere& sph);
	Sphere(float r, int sl, int st);

	void setRadius(float r);
	float getRadius() const;
	void setSlice(int sl);
	int getSlice() const;
	void setStack(int st);
	int getStack() const;
	void setLane(int ln);
	int getLane() const;

	virtual void draw() const;

	Sphere& operator=(const Sphere& sph);

private:
	float radius;
	int slice;
	int stack;
	int lane;
};

