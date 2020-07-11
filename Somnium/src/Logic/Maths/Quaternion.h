#pragma once

#include "Vector4.h"
#include "Vector3.h"
#include "Matrix4.h"

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

				struct {
					float x, y, z, w;
				};
			};

			static Quaternion fromEulerAngles(Vector3 eulerAngles);
			static Quaternion fromEulerAngles(float xAngle, float yAngle, float zAngle);
			static Quaternion fromAxisAngle(float angle, Maths::Vector3 axis);
			
			Vector3 toEulerAngles() const;

			Quaternion(float x, float y, float z, float w) { vw = Vector4(x, y, z, w); }

			Quaternion(Vector3 newV = Vector3(), float newW = 0)
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

			Quaternion& operator*=(const Quaternion &rhs);
			Quaternion operator*(const Quaternion& rhs) const;

			Quaternion& operator*=  (const float& scalar);
			Quaternion operator*  (const float &scalar) const;

			//TODO: Make operators global in order to have 2 way operator overloading

			float magnitude() const;
			Quaternion conjugate() const;
			Quaternion inverse() const;

			Quaternion slerp(const Quaternion &quaternion1, const Quaternion &quaternion2, float t) const;

			Matrix4 toTransformationMatrix() const;

			inline float dot(const Quaternion &quaternion);
			static inline float dot(const Quaternion &quaternion1, const Quaternion &quaternion2);

			inline void normalise();
			static inline Quaternion normalise(const Quaternion &quaternion);

			//TODO: Animation functions and variables
		};

		inline Quaternion operator- (const float &scalar, const Quaternion &quaternion)
		{
			return Quaternion(quaternion.vw - scalar);
		}

		inline Quaternion operator+ (const float &scalar, const Quaternion &quaternion)
		{
			return Quaternion(quaternion.vw + scalar);
		}

		inline Quaternion operator* (const float &scalar, const Quaternion &quaternion)
		{
			return Quaternion(quaternion.vw * scalar);
		}
	}
}
