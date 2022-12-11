#include "Sphere.h"

Sphere::Sphere() {
}
Sphere::Sphere(const Sphere& sph) {
	setCenter(sph.getCenter());
	setRadius(sph.getRadius());
	setVelocity(sph.getVelocity());
	setSlice(sph.getSlice());
	setStack(sph.getStack());
	setLane(sph.getLane());
	setAmbient(sph.getAmbient().toArray()[0], sph.getAmbient().toArray()[1], sph.getAmbient().toArray()[2], sph.getAmbient().toArray()[3]);
	setDiffuse(sph.getDiffuse().toArray()[0], sph.getDiffuse().toArray()[1], sph.getDiffuse().toArray()[2], sph.getDiffuse().toArray()[3]);
	setEmission(sph.getEmission().toArray()[0], sph.getEmission().toArray()[1], sph.getEmission().toArray()[2], sph.getEmission().toArray()[3]);
	setSpecular(sph.getSpecular().toArray()[0], sph.getSpecular().toArray()[1], sph.getSpecular().toArray()[2], sph.getSpecular().toArray()[3]);
	setShininess(sph.getShininess());
	setColor(sph.getColor());
}
Sphere::Sphere(float r, int sl, int st) {
	radius = r;
	slice = sl;
	stack = st;
}
void Sphere::setRadius(float r) {
	radius = r;
}
float Sphere::getRadius() const {
	return radius;
}
void Sphere::setSlice(int sl) {
	slice = sl;
}
int Sphere::getSlice() const {
	return slice;
}
void Sphere::setStack(int st) {
	stack = st;
}
int Sphere::getStack() const {
	return stack;
}
void Sphere::setLane(int ln) {
	lane = ln;
}
int Sphere::getLane() const {
	return lane;
}
void Sphere::draw() const {
	glPushMatrix();
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission.toArray());
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient.toArray());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse.toArray());
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular.toArray());
	glMaterialf(GL_FRONT, GL_SHININESS, getShininess());

	glTranslatef(center[0], center[1], center[2]);

	glutSolidSphere(radius, slice, stack);

	glPopMatrix();
}
Sphere& Sphere::operator=(const Sphere& sph) {
	radius = sph.getRadius();
	slice = sph.getSlice();
	stack = sph.getStack();
	lane = sph.getLane();
	center = sph.getCenter();
	velocity = sph.getVelocity();
	emission = sph.getEmission();
	ambient = sph.getAmbient();
	diffuse = sph.getDiffuse();
	specular = sph.getSpecular();
	shininess = sph.getShininess();
	color = sph.getColor();

	return (*this);
}