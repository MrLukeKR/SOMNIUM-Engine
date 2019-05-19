#include "Vector3.h"

#include <cmath>

namespace Somnium
{
	namespace Maths
	{
		Vector3  Vector3::operator+ (const Vector3& rhs) const
		{
			return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		Vector3& Vector3::operator+=(const Vector3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;

			return *this;
		}

		Vector3 Vector3::operator-() const
		{
			return Vector3(-x,-y,-z);
		}

		//Subtraction Operator
		Vector3  Vector3::operator- (const Vector3& rhs) const
		{
			return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		Vector3& Vector3::operator-=(const Vector3& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;

			return *this;
		}

		//Multiplication Operators
		Vector3  Vector3::operator* (const Vector3& rhs) const
		{
			return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
		}

		Vector3& Vector3::operator*=(const Vector3& rhs)
		{
			return *this = *this * rhs;
		}

		Vector3  Vector3::operator* (float scalar) const
		{
			return Vector3(x * scalar, y * scalar, z * scalar);
		}

		Vector3& Vector3::operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;

			return *this;
		}

		Vector3 Vector3::normalise() const
		{
			double mag = magnitude();
			return Vector3(x / mag, y / mag, z / mag);
		}

		double Vector3::magnitude() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		float Vector3::dot(const Vector3& vector) const
		{
			return x * vector.x + y * vector.y + z * vector.z;
		}

		float Vector3::dot(const Vector3& vector1, const Vector3& vector2)
		{
			return vector1.dot(vector2);
		}
	}
}
