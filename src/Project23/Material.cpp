#include "Material.h"

Material::Material() {
	emission.setPos(0, 0, 0, 0);
	ambient.setPos(0, 0, 0, 0);
	diffuse.setPos(0, 0, 0, 0);
	specular.setPos(0, 0, 0, 0);
	setShininess(0);
}
void Material::setEmission(float r, float g, float b, float a) {
	emission.setPos(r, g, b, a);
}
void Material::setAmbient(float r, float g, float b, float a) {
	ambient.setPos(r, g, b, a);
}
void Material::setDiffuse(float r, float g, float b, float a) {
	diffuse.setPos(r, g, b, a);
}
void Material::setSpecular(float r, float g, float b, float a) {
	specular.setPos(r, g, b, a);
}
void Material::setEmission(const Vector4f& v) {
	emission = v;
}
void Material::setAmbient(const Vector4f& v) {
	ambient = v;
}
void Material::setDiffuse(const Vector4f& v) {
	diffuse = v;
}
void Material::setSpecular(const Vector4f& v) {
	specular = v;
}
void Material::setShininess(float sh) {
	shininess = sh;
}
void Material::setColor(int col) {
	color = col;
}
Vector4f Material::getEmission() const {
	return emission;
}
Vector4f Material::getAmbient() const {
	return ambient;
}
Vector4f Material::getDiffuse() const {
	return diffuse;
}
Vector4f Material::getSpecular() const {
	return specular;
}
float Material::getShininess() const {
	return shininess;
}
int Material::getColor() const {
	return color;
}