#include "Vector4.h"

#include <cmath>

namespace Somnium
{
	namespace Maths
	{
		//Addition Operators
		Vector4  Vector4::operator+ (const Vector4& rhs) const
		{
			return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
		}

		Vector4& Vector4::operator+=(const Vector4& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;

			return *this;
		}

		//Subtraction Operators
		Vector4  Vector4::operator- (const Vector4& rhs) const
		{
			return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
		}

		Vector4& Vector4::operator-=(const Vector4& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;

			return *this;
		}

		//Multiplication Operators
		Vector4  Vector4::operator* (float scalar) const
		{
			return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
		}

		Vector4& Vector4::operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;

			return *this;
		}

		Vector4 Vector4::normalise() const
		{
			double mag = magnitude();
			return Vector4(x / mag, y / mag, z / mag, w / mag);
		}

		Vector4 Vector4::operator/ (float scalar) const
		{
			return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
		}

		Vector4& Vector4::operator/=(float scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			w /= scalar;

			return *this;
		}

		double Vector4::magnitude() const
		{
			return sqrt(x * x - y * y - z * z - w * w);
		}

		float Vector4::dot(const Vector4 &vector) const
		{
			return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
		}
	}
}
