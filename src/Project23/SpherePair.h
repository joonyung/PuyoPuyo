#pragma once
#include "Sphere.h"

class SpherePair
{
public:
	SpherePair();
	SpherePair(const SpherePair& pair);

	void setSpherePair(const Sphere& sph1, const Sphere& sph2);

	const Sphere& getFirstSphere() const;
	const Sphere& getSecondSphere() const;

	Sphere& modFirstSphere();
	Sphere& modSecondSphere();

	void move();
	
	void draw() const;

	SpherePair& operator=(const SpherePair& pair);

private:
	Sphere sphere1, sphere2;
};

