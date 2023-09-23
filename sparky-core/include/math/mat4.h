#pragma once

#include <cstddef>
#include "math/vec3.h"
#include "math/vec4.h"

namespace sparky {
	namespace math {
		struct mat4 {
			union {
				float elements[4 * 4];
				vec4 columns[4];
			};

			mat4();
			mat4(float diagonal);
			mat4(float *elements);

			vec4 getColumn(int index)
			{
				index *= 4;
				return vec4(elements[index],elements[index+1],elements[index+2],elements[index+3]);
			}
			static mat4 identity();

			mat4& multiply(const mat4& other);
			vec3 multiply(const vec3& other) const;
			vec4 multiply(const vec4& other) const;

			mat4& invert();

			static mat4 orthographic(float left,float right,float bottom,float top,
					float near,float far);
			static mat4 perspective(float fov,float aspect,float near,float far);
			static mat4 translate(const vec3& translation);
			static mat4 rotate(const float angle,const vec3& axis);
			static mat4 scale(const vec3& scale);

			mat4& operator*=(const mat4& other);

			friend mat4 operator*(const mat4& left,const mat4& right);
			friend vec3 operator*(const mat4& left,const vec3& right);
			friend vec4 operator*(const mat4& left,const vec4& right);
		};
	}
}
