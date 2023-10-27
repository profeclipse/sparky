#include "math/vec3.h"

namespace sparky {
	vec3::vec3() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	vec3::vec3(const float x,const float y,const float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3& vec3::add(const vec3& other) {
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;

		return *this;
	}

	vec3& vec3::subtract(const vec3& other) {
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;

		return *this;
	}

	vec3& vec3::multiply(const vec3& other) {
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;

		return *this;
	}

	vec3& vec3::divide(const vec3& other) {
		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;

		return *this;
	}

	vec3& vec3::add(const float other) {
		this->x += other;
		this->y += other;
		this->z += other;

		return *this;
	}

	vec3& vec3::subtract(const float other) {
		this->x -= other;
		this->y -= other;
		this->z -= other;

		return *this;
	}

	vec3& vec3::multiply(const float other) {
		this->x *= other;
		this->y *= other;
		this->z *= other;

		return *this;
	}

	vec3& vec3::divide(const float other) {
		this->x /= other;
		this->y /= other;
		this->z /= other;

		return *this;
	}

	vec3& vec3::operator+=(const vec3& other) {
		return add(other);
	}

	vec3& vec3::operator-=(const vec3& other) {
		return subtract(other);
	}

	vec3& vec3::operator*=(const vec3& other) {
		return multiply(other);
	}

	vec3& vec3::operator/=(const vec3& other) {
		return divide(other);
	}

	vec3& vec3::operator+=(const float other) {
		return add(other);
	}

	vec3& vec3::operator-=(const float other) {
		return subtract(other);
	}

	vec3& vec3::operator*=(const float other) {
		return multiply(other);
	}

	vec3& vec3::operator/=(const float other) {
		return divide(other);
	}

	bool vec3::operator==(const vec3& other) {
		return x == other.x && y == other.y && z == other.z;
	}

	bool vec3::operator!=(const vec3& other) {
		return !(*this == other);
	}

	vec3 operator+(const vec3& left,const vec3& right) {
		vec3 v(left);
		return v.add(right);
	}

	vec3 operator-(const vec3& left,const vec3& right) {
		vec3 v(left);
		return v.subtract(right);
	}

	vec3 operator*(const vec3& left,const vec3& right) {
		vec3 v(left);
		return v.multiply(right);
	}

	vec3 operator/(const vec3& left,const vec3& right) {
		vec3 v(left);
		return v.divide(right);
	}

	vec3 operator+(const vec3& left,const float right) {
		vec3 v(left);
		return v.add(right);
	}

	vec3 operator-(const vec3& left,const float right) {
		vec3 v(left);
		return v.subtract(right);
	}

	vec3 operator*(const vec3& left,const float right) {
		vec3 v(left);
		return v.multiply(right);
	}

	vec3 operator/(const vec3& left,const float right) {
		vec3 v(left);
		return v.divide(right);
	}

	std::ostream& operator<<(std::ostream& stream,const vec3& vector) {
		stream << "vec3:(" << vector.x << "," << vector.y << "," << vector.z << ")";

		return stream;
	}
}
