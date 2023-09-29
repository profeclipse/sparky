#include "math/vec4.h"

namespace sparky {
	vec4::vec4() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}

	vec4::vec4(const float x,const float y,const float z,const float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	vec4& vec4::add(const vec4& other) {
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		this->w += other.w;

		return *this;
	}

	vec4& vec4::subtract(const vec4& other) {
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		this->w -= other.w;

		return *this;
	}

	vec4& vec4::multiply(const vec4& other) {
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
		this->w *= other.w;

		return *this;
	}

	vec4& vec4::divide(const vec4& other) {
		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;
		this->w /= other.w;

		return *this;
	}

	vec4& vec4::add(const float other) {
		this->x += other;
		this->y += other;
		this->z += other;
		this->w += other;

		return *this;
	}

	vec4& vec4::subtract(const float other) {
		this->x -= other;
		this->y -= other;
		this->z -= other;
		this->w -= other;

		return *this;
	}

	vec4& vec4::multiply(const float other) {
		this->x *= other;
		this->y *= other;
		this->z *= other;
		this->w *= other;

		return *this;
	}

	vec4& vec4::divide(const float other) {
		this->x /= other;
		this->y /= other;
		this->z /= other;
		this->w /= other;

		return *this;
	}

	vec4& vec4::operator+=(const vec4& other) {
		return add(other);
	}

	vec4& vec4::operator-=(const vec4& other) {
		return subtract(other);
	}

	vec4& vec4::operator*=(const vec4& other) {
		return multiply(other);
	}

	vec4& vec4::operator/=(const vec4& other) {
		return divide(other);
	}

	vec4& vec4::operator+=(const float other) {
		return add(other);
	}

	vec4& vec4::operator-=(const float other) {
		return subtract(other);
	}

	vec4& vec4::operator*=(const float other) {
		return multiply(other);
	}

	vec4& vec4::operator/=(const float other) {
		return divide(other);
	}

	bool vec4::operator==(const vec4& other) {
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	bool vec4::operator!=(const vec4& other) {
		return !(*this == other);
	}

	vec4 operator+(const vec4& left,const vec4& right) {
		vec4 v(left);
		return v.add(right);
	}

	vec4 operator-(const vec4& left,const vec4& right) {
		vec4 v(left);
		return v.subtract(right);
	}

	vec4 operator*(const vec4& left,const vec4& right) {
		vec4 v(left);
		return v.multiply(right);
	}

	vec4 operator/(const vec4& left,const vec4& right) {
		vec4 v(left);
		return v.divide(right);
	}

	vec4 operator+(const vec4& left,const float right) {
		vec4 v(left);
		return v.add(right);
	}

	vec4 operator-(const vec4& left,const float right) {
		vec4 v(left);
		return v.subtract(right);
	}

	vec4 operator*(const vec4& left,const float right) {
		vec4 v(left);
		return v.multiply(right);
	}

	vec4 operator/(const vec4& left,const float right) {
		vec4 v(left);
		return v.divide(right);
	}

	std::ostream& operator<<(std::ostream& stream,const vec4& vector) {
		stream << "vec4:(" << vector.x << "," << vector.y << ","
			<< vector.z << "," << vector.w << ")";

		return stream;
	}
}
