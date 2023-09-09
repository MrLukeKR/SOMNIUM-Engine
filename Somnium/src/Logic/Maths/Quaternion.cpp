#include "Quaternion.h"

#include <algorithm>

namespace Somnium
{
	namespace Maths
	{
		Quaternion Quaternion::fromAxisAngle(float angle, Maths::Vector3 axis)
		{
			float halfAngle = angle * .5f;
			float sinA = sin(halfAngle);
			Quaternion q;

			q.x = axis.x * sinA;
			q.y = axis.y * sinA;
			q.z = axis.z * sinA;
			q.w_sep = cos(halfAngle);

			return q;
		}

		Quaternion Quaternion::fromEulerAngles(Vector3 eulerAngles)
		{
			return fromEulerAngles(eulerAngles.x, eulerAngles.y, eulerAngles.z);
		}

		Quaternion Quaternion::fromEulerAngles(float xAngle, float yAngle, float zAngle)
		{
			// std::cout << "Euler: (" << xAngle << ", " << yAngle << ", " << zAngle << ")\t";

			Quaternion newQ;

			float cosX = cos(xAngle * 0.5),
				  sinX = sin(xAngle * 0.5),
				  cosY = cos(yAngle * 0.5),
				  sinY = sin(yAngle * 0.5),
				  cosZ = cos(zAngle * 0.5),
				  sinZ = sin(zAngle * 0.5);

			newQ.w_sep = cosZ * cosY * cosX + sinZ * sinY * sinX;
			newQ.x = sinZ * cosY * cosX - cosZ * sinY * sinX;
			newQ.y = cosZ * sinY * cosX + sinZ * cosY * sinX;
			newQ.z = cosZ * cosY * sinX - sinZ * sinY * cosX;

			Vector3 angles = newQ.toEulerAngles();

			// std::cout << "Quaternion: (" << angles.x << ", " << angles.y << ", " << angles.z << ")" << std::endl;

			return newQ;
		}

		Vector3 Quaternion::toEulerAngles() const
		{
			Vector3 eulerAngles;

			float sinX_cosY = 2 * (w_sep * x, + y * z);
			float cosX_cosY = 1 - 2 * (x * x + y * y);
			float sinY = 2 * (w_sep * y - z * x);
			float sinZ_cosY = 2 * (w_sep * z + x * y);
			float cosZ_cosY = 1 - 2 * (y * y + z * z);
			
			eulerAngles.x = atan2(sinX_cosY, cosX_cosY);
			eulerAngles.y = abs(sinY) >= 1 ? copysign(PI / 2, sinY) : asin(sinY);
			eulerAngles.z = atan2(sinZ_cosY, cosZ_cosY);

			return eulerAngles;
		}

		Quaternion& Quaternion::operator+=(const Quaternion &rhs)
		{
			vw += rhs.vw;
			return *this;
		}

		Quaternion Quaternion::operator+(const Quaternion &rhs) const
		{
			return Quaternion(vw + rhs.vw);
		}

		Quaternion &Quaternion::operator+=(const float &scalar)
		{
			vw += scalar;
			return *this;
		}

		Quaternion Quaternion::operator+(const float &scalar) const
		{
			return Quaternion(vw + scalar);
		}

		Quaternion& Quaternion::operator-=(const Quaternion &rhs)
		{
			vw -= rhs.vw;
			return *this;
		}

		Quaternion Quaternion::operator-(const Quaternion &rhs) const
		{
			return Quaternion(vw - rhs.vw);
		}

		Quaternion& Quaternion::operator-=(const float &scalar)
		{
			vw -= scalar;

			return *this;
		}

		Quaternion Quaternion::operator-(const float &scalar) const
		{
			return Quaternion(vw - scalar);
		}

		Quaternion Quaternion::operator*(const Quaternion& rhs) const
		{
			// Grassman product
			float angle = w_sep * rhs.w_sep - v.dot(rhs.v);

			Maths::Vector3 imaginary = rhs.v * w_sep + v * rhs.w_sep + v * rhs.v;

			return Quaternion(imaginary, angle);
		}

		Quaternion& Quaternion::operator*=(const Quaternion &rhs)
		{
			(*this) = (*this) * rhs;

			return *this;
		}

		Quaternion Quaternion::operator* (const float &scalar) const
		{
			return Quaternion(vw * scalar);
		}

		Quaternion& Quaternion::operator*= (const float& scalar)
		{
			vw *= scalar;

			return *this;
		}

		float Quaternion::magnitude() const
		{
			return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + w_sep * w_sep);
		}

		Quaternion Quaternion::inverse() const
		{
			Quaternion conj = conjugate();

			return conj * (1 / magnitude());
		}

		Quaternion Quaternion::conjugate() const
		{
			return Quaternion(-v, w_sep);
		}

		Matrix4 Quaternion::toTransformationMatrix() const
		{
			Matrix4 transformationMatrix = Matrix4::identity();

			Vector4 nvw = vw / (float)sqrt(dot(vw, vw)); // Normalised vw vector

			float
				xSq = x * x,
				ySq = y * y,
				zSq = z * z,
				xy  = x * y,
				zw  = z * w_sep,
				yw  = y * w_sep,
				yz  = y * z,
				xw  = x * w_sep,
				xz  = x * z;

			transformationMatrix.elements2D[0][0] = 1 - 2 * (ySq + zSq);
			transformationMatrix.elements2D[1][0] = 2 * (xy + zw);
			transformationMatrix.elements2D[2][0] = 2 * xz - yw;

			transformationMatrix.elements2D[0][1] = 2 * (xy - zw);
			transformationMatrix.elements2D[1][1] = 1 - 2 * (xSq + zSq);
			transformationMatrix.elements2D[2][1] = 2 * (yz + xw);

			transformationMatrix.elements2D[0][2] = 2 * (xz + yw);
			transformationMatrix.elements2D[1][2] = 2 * (yz - xw);
			transformationMatrix.elements2D[2][2] = 1 - 2 * (xSq + ySq);

			return transformationMatrix;
		}

		Quaternion Quaternion::slerp(const Quaternion &quaternion1, const Quaternion &quaternion2, float t) const
		{
			float cosineTheta = dot(quaternion1, quaternion2);
			if (cosineTheta > .9995f)
				return normalise((1 - t) * quaternion1 + t * quaternion2);
			else
			{
				float theta = acos(clamp(cosineTheta, -1, 1));
				float thetaT = theta * t;
				Quaternion qperp = normalise(quaternion2 - quaternion1 * cosineTheta);
				return quaternion1 * cos(thetaT) + qperp * sin(thetaT);
			}
		}

		inline void Quaternion::normalise()
		{
			vw /= (float)sqrt(dot(vw, vw));
		}

		inline float Quaternion::dot(const Quaternion &quaternion)
		{
			return dot(*this, quaternion);
		}

		inline float Quaternion::dot(const Quaternion & quaternion1, const Quaternion & quaternion2)
		{
			return Vector3::dot(quaternion1.v, quaternion2.v) + quaternion1.w_sep * quaternion2.w_sep;
		}

		inline Quaternion Quaternion::normalise(const Quaternion &quaternion)
		{
			return Quaternion(quaternion.vw / (float)sqrt(dot(quaternion, quaternion)));
		}
	}
}
