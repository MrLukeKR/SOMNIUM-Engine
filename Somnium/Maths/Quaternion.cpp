#include "Quaternion.h"

namespace Somnium
{
	namespace Maths
	{
		Quaternion& Quaternion::operator+=(const Quaternion &rhs)
		{
			vw += rhs.vw;
			return *this;
		}

		Quaternion& Quaternion::operator-=(const Quaternion &rhs)
		{
			vw -= rhs.vw;
			return *this;
		}

		Matrix4 Quaternion::toTransformationMatrix() const
		{
			Matrix4 transformationMatrix = Matrix4::identity();

			float 
				xSq = vw.x * vw.x,
				ySq = vw.y * vw.y,
				zSq = vw.z * vw.z,
				xy  = vw.x * vw.y,
				zw  = vw.z * vw.w,
				yw  = vw.y * vw.w,
				yz  = vw.y * vw.z,
				xw  = vw.x * vw.w,
				xz  = vw.x * vw.z;

			transformationMatrix.elements2D[0][0] = 1 - 2 * (ySq + zSq);
			transformationMatrix.elements2D[1][0] = 2 * (xy + zw);
			transformationMatrix.elements2D[2][0] = 2 * xz - yw;

			transformationMatrix.elements2D[0][1] = 2 * (xy - zw);
			transformationMatrix.elements2D[1][1] = 1 - 2 * (xSq + zSq);
			transformationMatrix.elements2D[2][1] = 2 * (yz + xw);

			transformationMatrix.elements2D[0][2] = 2 * (xz + yw);
			transformationMatrix.elements2D[1][2] = 2 * (yz - xw);
			transformationMatrix.elements2D[2][2] = 1 - 2 * (xSq + ySq);

			return Matrix4();
		}

		float Quaternion::slerp(const Quaternion &quaternion1, const Quaternion &quaternion2, float t) const
		{
			float cosineTheta = dot(quaternion1, quaternion2);
			if (cosineTheta > .9995f)
				return normalise(quaternion1 * (1 - t) + quaternion2 * t);
		}

		inline float Quaternion::dot(const Quaternion &quaternion)
		{
			return dot(*this, quaternion);
		}

		inline float dot(const Quaternion &quaternion1, const Quaternion &quaternion2)
		{
			return Vector3::dot(quaternion1.v, quaternion2.v) + quaternion1.w * quaternion2.w;
		}

		inline Quaternion Quaternion::normalise(const Quaternion &quaternion)
		{
			return Quaternion(quaternion.vw / (float)sqrt(dot(quaternion, quaternion)));
		}
	}
}