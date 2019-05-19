#include "Vector2.h"

#include <cmath>

using namespace std;

namespace Somnium
{
	namespace Maths
	{
		Vector2 Vector2::operator+(const Vector2& rhs) const
		{
			return Vector2(x + rhs.x, y + rhs.y);
		}

		Vector2& Vector2::operator+=(const Vector2& rhs) {
			x += rhs.x;
			y += rhs.y;

			return *this;
		}

		Vector2 Vector2::operator-(const Vector2& rhs) const {
			return Vector2(x - rhs.x, y - rhs.y);
		}

		Vector2& Vector2::operator-=(const Vector2& rhs) {
			x -= rhs.x;
			y -= rhs.y;

			return *this;
		}

		Vector2 Vector2::operator*(float val) const {
			return Vector2(x * val, y * val);
		}

		Vector2& Vector2::operator*=(float val) {
			x *= val;
			y *= val;

			return *this;
		}

		Vector2 Vector2::normalise() const
		{
			double mag = magnitude();
			return Vector2(x / mag, y / mag);
		}

		double Vector2::magnitude() const {
			return sqrt(x * x + y * y);
		}

		float Vector2::dot(const Vector2 &vector) const
		{
			return x * vector.x + y * vector.y;
		}
	}
}
