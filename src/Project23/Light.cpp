#include "Light.h"

Light::Light(int x, int y, int z, int L_ID) {
	pos.setPos(x, y, z);
	lightID = L_ID;
}
void Light::setAmbient(float r, float g, float b, float a) {
	ambient.setPos(r, g, b, a);
}
void Light::setDiffuse(float r, float g, float b, float a) {
	diffuse.setPos(r, g, b, a);
}
void Light::setSpecular(float r, float g, float b, float a) {
	specular.setPos(r, g, b, a);
}
int Light::getID() {
	return lightID;
}
void Light::draw() const {
	glLightfv(lightID, GL_AMBIENT, ambient.toArray());
	glLightfv(lightID, GL_DIFFUSE, diffuse.toArray());
	glLightfv(lightID, GL_SPECULAR, specular.toArray());
	glLightfv(lightID, GL_POSITION, pos.toArray());
}