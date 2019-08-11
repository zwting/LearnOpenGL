#pragma once
#include <cmath>

template <typename T>
class Vec3
{
public:
	T x, y, z;

	Vec3(T x, T y, T z = 0) : x(x), y(y), z(z)
	{
	}

	Vec3(): x(0), y(0), z(0)
	{
	}

	Vec3(T val): x(val), y(val), z(val)
	{
	}

	Vec3 operator+(const Vec3& rhs) const
	{
		return {this->x + rhs.x, this->y + rhs.y, this->z + rhs.z};
	}

	Vec3 operator+(const T& scalar) const
	{
		return {this->x + scalar, this->y + scalar, this.z + scalar};
	}

	Vec3 operator-(const Vec3& rhs) const
	{
		return *this + (-rhs);
	}

	Vec3 operator-(const T& scalar) const
	{
		return *this + (-scalar);
	}

	Vec3 operator-() const
	{
		return {-this->x, -this->y, -this->z};
	}

	Vec3 operator*(const Vec3& rhs) const
	{
		return {this->x * rhs.x, this->y * rhs.y, this->z * rhs.z};
	}

	T magnitude() const
	{
		return sqrt(this->sqrMagnitude());
	}

	T sqrMagnitude() const
	{
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	static T Dot(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	static Vec3 Cross(const Vec3& lhs, const Vec3& rhs)
	{
		return {
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
		};
	}
};
