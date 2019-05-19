#pragma once

#include <stdio.h>
#include <string>

namespace Somnium
{
	namespace Maths
	{
		struct Vector2
		{
			float x, y;

			Vector2(float x = 0, float y = 0)
				: x(x), y(y) {};

			~Vector2() {};

			//Addition Operators
			Vector2  operator+ (const Vector2&) const;
			Vector2& operator+=(const Vector2&);

			//Subtraction Operators
			Vector2  operator- (const Vector2&) const;
			Vector2& operator-=(const Vector2&);

			//Multiplication Operators
			Vector2  operator* (float) const;
			Vector2& operator*=(float);

			Vector2 normalise() const;
			float dot(const Vector2& vector) const;

			double magnitude(void) const;

			std::string toString()
			{
				char buff[256];
				sprintf_s(buff, "[%f, %f]", x, y);

				return std::string(buff);
			}
		};
	}
}
