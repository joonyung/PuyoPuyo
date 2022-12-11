#pragma once
class Vector3f
{
public:
	Vector3f();
	Vector3f(float x, float y, float z);
	void setPos(float x, float y, float z);

	float& operator[](const int i);
	float operator[](const int i) const;

	const float* toArray() const;

	Vector3f& operator=(const Vector3f& v);
	Vector3f& operator+=(const Vector3f& v);
	Vector3f& operator-=(const Vector3f& v);
	Vector3f& operator*=(float s);

private:
	float pos[3];
};

Vector3f operator+(const Vector3f& v1, const Vector3f& v2);
Vector3f operator-(const Vector3f& v1, const Vector3f& v2);
Vector3f operator*(float s, const Vector3f& v);
