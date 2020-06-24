#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include <math.h>

#define PI 3.14159265358979323846f

namespace Somnium
{
	namespace Maths
	{
		inline float toRadians(float degrees)
		{
			return degrees * (PI / 180.0f);
		}

		inline float toDegrees(float radians)
		{
			return radians * (180.0f / PI);
		}

		template<typename Type, typename T1, typename T2>
		inline Type clamp(const Type &value, const T1 &min, const T2 &max)
		{
			if (value > (Type)max) return (Type)max;
			if (value < (Type)min) return (Type)min;
			return value;
		}
	}
}
