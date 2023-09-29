#include "math/vec2.h"

namespace sparky {
	vec2::vec2() {
		x = 0.0f;
		y = 0.0f;
	}

	vec2::vec2(const float x,const float y) {
		this->x = x;
		this->y = y;
	}

	vec2& vec2::add(const vec2& other) {
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	vec2& vec2::subtract(const vec2& other) {
		this->x -= other.x;
		this->y -= other.y;

		return *this;
	}

	vec2& vec2::multiply(const vec2& other) {
		this->x *= other.x;
		this->y *= other.y;

		return *this;
	}

	vec2& vec2::divide(const vec2& other) {
		this->x /= other.x;
		this->y /= other.y;

		return *this;
	}

	vec2& vec2::add(const float other) {
		this->x += other;
		this->y += other;

		return *this;
	}

	vec2& vec2::subtract(const float other) {
		this->x -= other;
		this->y -= other;

		return *this;
	}

	vec2& vec2::multiply(const float other) {
		this->x *= other;
		this->y *= other;

		return *this;
	}

	vec2& vec2::divide(const float other) {
		this->x /= other;
		this->y /= other;

		return *this;
	}

	vec2& vec2::operator+=(const vec2& other) {
		return add(other);
	}

	vec2& vec2::operator-=(const vec2& other) {
		return subtract(other);
	}

	vec2& vec2::operator*=(const vec2& other) {
		return multiply(other);
	}

	vec2& vec2::operator/=(const vec2& other) {
		return divide(other);
	}

	vec2& vec2::operator+=(const float other) {
		return add(other);
	}

	vec2& vec2::operator-=(const float other) {
		return subtract(other);
	}

	vec2& vec2::operator*=(const float other) {
		return multiply(other);
	}

	vec2& vec2::operator/=(const float other) {
		return divide(other);
	}

	bool vec2::operator==(const vec2& other) {
		return x == other.x && y == other.y;
	}

	bool vec2::operator!=(const vec2& other) {
		return !(*this == other);
	}

	vec2 operator+(const vec2& left,const vec2& right) {
		vec2 v(left);
		return v.add(right);
	}

	vec2 operator-(const vec2& left,const vec2& right) {
		vec2 v(left);
		return v.subtract(right);
	}

	vec2 operator*(const vec2& left,const vec2& right) {
		vec2 v(left);
		return v.multiply(right);
	}

	vec2 operator/(const vec2& left,const vec2& right) {
		vec2 v(left);
		return v.divide(right);
	}

	vec2 operator+(const vec2& left,const float right) {
		vec2 v(left);
		return v.add(right);
	}

	vec2 operator-(const vec2& left,const float right) {
		vec2 v(left);
		return v.subtract(right);
	}

	vec2 operator*(const vec2& left,const float right) {
		vec2 v(left);
		return v.multiply(right);
	}

	vec2 operator/(const vec2& left,const float right) {
		vec2 v(left);
		return v.divide(right);
	}

	std::ostream& operator<<(std::ostream& stream,const vec2& vector) {
		stream << "vec2:(" << vector.x << "," << vector.y << ")";

		return stream;
	}
}
