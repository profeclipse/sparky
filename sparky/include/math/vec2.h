#pragma once
#include <iostream>

namespace sparky {
	struct vec2 {
		float x,y;

		vec2();
		vec2(const float x,const float y);

		vec2& add(const vec2& other);
		vec2& subtract(const vec2& other);
		vec2& multiply(const vec2& other);
		vec2& divide(const vec2& other);
		vec2& add(const float other);
		vec2& subtract(const float other);
		vec2& multiply(const float other);
		vec2& divide(const float other);

		vec2& operator+=(const vec2& other);
		vec2& operator-=(const vec2& other);
		vec2& operator*=(const vec2& other);
		vec2& operator/=(const vec2& other);
		vec2& operator+=(const float other);
		vec2& operator-=(const float other);
		vec2& operator*=(const float other);
		vec2& operator/=(const float other);

		bool operator==(const vec2& other);
		bool operator!=(const vec2& other);

		friend vec2 operator+(const vec2& left,const vec2& right);
		friend vec2 operator-(const vec2& left,const vec2& right);
		friend vec2 operator*(const vec2& left,const vec2& right);
		friend vec2 operator/(const vec2& left,const vec2& right);
		friend vec2 operator+(const vec2& left,const float right);
		friend vec2 operator-(const vec2& left,const float right);
		friend vec2 operator*(const vec2& left,const float right);
		friend vec2 operator/(const vec2& left,const float right);

		friend std::ostream& operator<<(std::ostream& stream,const vec2& vector);
	};
}
