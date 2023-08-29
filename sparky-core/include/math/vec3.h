#pragma once
#include <iostream>

namespace sparky {
	namespace math {
		struct vec3 {
			float x,y,z;

			vec3();
			vec3(const float x,const float y,const float z);

			vec3& add(const vec3& other);
			vec3& subtract(const vec3& other);
			vec3& multiply(const vec3& other);
			vec3& divide(const vec3& other);
			vec3& add(const float other);
			vec3& subtract(const float other);
			vec3& multiply(const float other);
			vec3& divide(const float other);

			vec3& operator+=(const vec3& other);
			vec3& operator-=(const vec3& other);
			vec3& operator*=(const vec3& other);
			vec3& operator/=(const vec3& other);
			vec3& operator+=(const float other);
			vec3& operator-=(const float other);
			vec3& operator*=(const float other);
			vec3& operator/=(const float other);

			bool operator==(const vec3& other);
			bool operator!=(const vec3& other);

			friend vec3 operator+(const vec3& left,const vec3& right);
			friend vec3 operator-(const vec3& left,const vec3& right);
			friend vec3 operator*(const vec3& left,const vec3& right);
			friend vec3 operator/(const vec3& left,const vec3& right);
			friend vec3 operator+(const vec3& left,const float right);
			friend vec3 operator-(const vec3& left,const float right);
			friend vec3 operator*(const vec3& left,const float right);
			friend vec3 operator/(const vec3& left,const float right);

			friend std::ostream& operator<<(std::ostream& stream,const vec3& vector);
		};
	}
}
