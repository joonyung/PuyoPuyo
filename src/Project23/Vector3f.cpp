#include "Vector3f.h"

Vector3f::Vector3f() {
	setPos(0, 0, 0);
}
Vector3f::Vector3f(float x, float y, float z) {
	setPos(x, y, z);
}
void Vector3f::setPos(float x, float y, float z) {
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}
float& Vector3f::operator[](const int i) {
	return pos[i];
}
float Vector3f::operator[](const int i) const {
	return pos[i];
}
const float* Vector3f::toArray() const {
	return pos;
}
Vector3f& Vector3f::operator=(const Vector3f& v) {
	pos[0] = v[0];
	pos[1] = v[1];
	pos[2] = v[2];

	return (*this);
}
Vector3f& Vector3f::operator+=(const Vector3f& v) {
	pos[0] += v[0];
	pos[1] += v[1];
	pos[2] += v[2];

	return (*this);
}
Vector3f& Vector3f::operator-=(const Vector3f& v) {
	pos[0] -= v[0];
	pos[1] -= v[1];
	pos[2] -= v[2];

	return (*this);
}
Vector3f& Vector3f::operator*=(float s) {
	pos[0] *= s;
	pos[1] *= s;
	pos[2] *= s;

	return (*this);
}
Vector3f operator+(const Vector3f& v1, const Vector3f& v2) {
	return Vector3f(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}
Vector3f operator-(const Vector3f& v1, const Vector3f& v2) {
	return Vector3f(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}
Vector3f operator*(float s, const Vector3f& v) {
	return Vector3f(s * v[0], s * v[1], s * v[2]);
}