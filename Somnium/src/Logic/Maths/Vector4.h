#pragma once

#include <stdio.h>
#include <string>

namespace Somnium
{
	namespace Maths
	{
		struct Vector4
		{
			float x, y, z, w;

			Vector4(float x = 0, float y = 0, float z = 0, float w = 0)
				: x(x), y(y), z(z), w(w) {};

			~Vector4() {};

			//Addition Operators
			Vector4  operator+ (const Vector4&) const;
			Vector4& operator+=(const Vector4&);

			//Subtraction Operators
			Vector4  operator- (const Vector4&) const;
			Vector4& operator-=(const Vector4&);

			//Multiplication Operators
			Vector4  operator* (float) const;
			Vector4& operator*=(float);

			//Division Operators
			Vector4  operator/ (float) const;
			Vector4& operator/=(float);

			Vector4 normalise() const;
			float dot(const Vector4 &vector) const;

			double magnitude(void) const;

			std::string toString()
			{
				char buff[256];
				sprintf_s(buff, "[%f, %f, %f, %f]", x, y, z, w);

				return std::string(buff);
			}
		};
	}
}
