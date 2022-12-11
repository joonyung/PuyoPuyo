#include "SpherePair.h"

SpherePair::SpherePair() {
}
SpherePair::SpherePair(const SpherePair& pair) {
	setSpherePair(pair.getFirstSphere(), pair.getSecondSphere());
}
void SpherePair::setSpherePair(const Sphere& sph1, const Sphere& sph2) {
	sphere1.setCenter(sph1.getCenter());
	sphere1.setRadius(sph1.getRadius());
	sphere1.setVelocity(sph1.getVelocity());
	sphere1.setSlice(sph1.getSlice());
	sphere1.setStack(sph1.getStack());
	sphere1.setLane(sph1.getLane());
	sphere1.setColor(sph1.getColor());
	sphere1.setAmbient(sph1.getAmbient().toArray()[0], sph1.getAmbient().toArray()[1], sph1.getAmbient().toArray()[2], sph1.getAmbient().toArray()[3]);
	sphere1.setDiffuse(sph1.getDiffuse().toArray()[0], sph1.getDiffuse().toArray()[1], sph1.getDiffuse().toArray()[2], sph1.getDiffuse().toArray()[3]);
	sphere1.setEmission(sph1.getEmission().toArray()[0], sph1.getEmission().toArray()[1], sph1.getEmission().toArray()[2], sph1.getEmission().toArray()[3]);
	sphere1.setSpecular(sph1.getSpecular().toArray()[0], sph1.getSpecular().toArray()[1], sph1.getSpecular().toArray()[2], sph1.getSpecular().toArray()[3]);
	sphere1.setShininess(sph1.getShininess());
	sphere1.setColor(sph1.getColor());
	sphere2.setCenter(sph2.getCenter());
	sphere2.setRadius(sph2.getRadius());
	sphere2.setVelocity(sph2.getVelocity());
	sphere2.setSlice(sph2.getSlice());
	sphere2.setStack(sph2.getStack());
	sphere2.setLane(sph2.getLane());
	sphere2.setColor(sph2.getColor());
	sphere2.setAmbient(sph2.getAmbient().toArray()[0], sph2.getAmbient().toArray()[1], sph2.getAmbient().toArray()[2], sph2.getAmbient().toArray()[3]);
	sphere2.setDiffuse(sph2.getDiffuse().toArray()[0], sph2.getDiffuse().toArray()[1], sph2.getDiffuse().toArray() [2], sph2.getDiffuse().toArray()[3]);
	sphere2.setEmission(sph2.getEmission().toArray()[0], sph2.getEmission().toArray()[1], sph2.getEmission().toArray()[2], sph2.getEmission().toArray()[3]);
	sphere2.setSpecular(sph2.getSpecular().toArray()[0], sph2.getSpecular().toArray()[1], sph2.getSpecular().toArray()[2], sph2.getSpecular().toArray()[3]);
	sphere2.setShininess(sph2.getShininess());
	sphere2.setColor(sph2.getColor());
}
const Sphere& SpherePair::getFirstSphere() const {
	return sphere1;
}
Sphere& SpherePair::modFirstSphere() {
	return sphere1;
}
Sphere& SpherePair::modSecondSphere() {
	return sphere2;
}
const Sphere& SpherePair::getSecondSphere() const {
	return sphere2;
}
void SpherePair::move() {
	sphere1.move();
	sphere2.move();
}
void SpherePair::draw() const {
	sphere1.draw();
	sphere2.draw();
}
SpherePair& SpherePair::operator=(const SpherePair& pair) {
	sphere1 = pair.getFirstSphere();
	sphere2 = pair.getSecondSphere();
	
	return (*this);
}