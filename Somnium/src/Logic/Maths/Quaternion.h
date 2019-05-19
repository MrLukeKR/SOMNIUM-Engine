#pragma once
#include "Maths.h"

namespace Somnium
{
	namespace Maths
	{
		struct Quaternion
		{
		public :
			union
			{
				Vector4 vw = Vector4();
				struct {
					Vector3 v;
					float w;
				};
			};

			Quaternion(float x = 0, float y = 0, float z = 0, float w = 1) { vw = Vector4(x, y, z, w); }

			Quaternion(Vector3 newV, float newW = 1)
			{
				v = newV;
				w = newW;
			}

			Quaternion(Vector4 newVW ) { vw = newVW; }

			~Quaternion() { };

			Quaternion &operator+=(const Quaternion &rhs);
			Quaternion operator+  (const Quaternion &rhs) const;
			Quaternion &operator+=(const float &scalar);
			Quaternion operator+  (const float &scalar) const;

			Quaternion &operator-=(const Quaternion &rhs);
			Quaternion operator-  (const Quaternion &rhs) const;
			Quaternion &operator-=(const float &scalar);
			Quaternion operator-  (const float &scalar) const;

			Quaternion &operator*=(const Quaternion &rhs);
			Quaternion operator*  (const float &scalar) const;

			//TODO: Make operators global in order to have 2 way operator overloading

			Quaternion &operator/=(const Quaternion &rhs);
			Quaternion operator/ (const float &scalar) const;

			Quaternion slerp(const Quaternion &quaternion1, const Quaternion &quaternion2, float t) const;

			Matrix4 toTransformationMatrix() const;

			inline float dot(const Quaternion &quaternion);
			static inline float dot(const Quaternion &quaternion1, const Quaternion &quaternion2);

			static inline Quaternion normalise(const Quaternion &quaternion);

			//TODO: Animation functions and variables
		};

		Quaternion operator- (const float &scalar, const Quaternion &quaternion)
		{
			return Quaternion(quaternion.vw - scalar);
		}

		Quaternion operator+ (const float &scalar, const Quaternion &quaternion)
		{
			return Quaternion(quaternion.vw + scalar);
		}

		Quaternion operator* (const float &scalar, const Quaternion &quaternion)
		{
			return Quaternion(quaternion.vw * scalar);
		}
	}
}
