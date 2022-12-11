#include "Vector4f.h"

Vector4f::Vector4f() {
	setPos(0, 0, 0, 0);
}
Vector4f::Vector4f(float x, float y, float z, float w) {
	setPos(x, y, z, w);
}
void Vector4f::setPos(float x, float y, float z, float w) {
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	pos[3] = w;
}
float& Vector4f::operator[](const int i) {
	return pos[i];
}
float Vector4f::operator[](const int i) const {
	return pos[i];
}
const float* Vector4f::toArray() const {
	return pos;
}
Vector4f& Vector4f::operator=(const Vector4f& v) {
	pos[0] = v[0];
	pos[1] = v[1];
	pos[2] = v[2];
	pos[3] = v[3];

	return (*this);
}
Vector4f& Vector4f::operator+=(const Vector4f& v) {
	pos[0] += v[0];
	pos[1] += v[1];
	pos[2] += v[2];
	pos[3] += v[3];

	return (*this);
}
Vector4f& Vector4f::operator-=(const Vector4f& v) {
	pos[0] -= v[0];
	pos[1] -= v[1];
	pos[2] -= v[2];
	pos[3] -= v[3];

	return (*this);
}
Vector4f operator+(const Vector4f& v1, const Vector4f& v2) {
	return Vector4f(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2], v1[3] + v2[3]);
}
Vector4f operator-(const Vector4f& v1, const Vector4f& v2) {
	return Vector4f(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2], v1[3] - v2[3]);
}
Vector4f operator*(float s, const Vector4f& v) {
	return Vector4f(s * v[0], s * v[1], s * v[2], s * v[3]);
}