#include "RenderableObject.h"

namespace Somnium
{
	namespace Graphics
	{
		void RenderableObject::update() 
		{

		}

		void RenderableObject::setPosition(float x, float y, float z)
		{
			//TODO: RESET TO (0,0,0) first
			move(-m_Position);
			move(Maths::Vector3(x, y, z));
		}

		void RenderableObject::setScale(float x, float y, float z)
		{
			m_Scale = Maths::Vector3(x, y, z);
		}

		void RenderableObject::setOrientation(float x, float y, float z)
		{
			m_Mesh->setOrientation(Maths::Vector3(x, y, z));
		}

		void RenderableObject::rotate(Maths::Vector3 rotation)
		{
			m_Mesh->rotate(rotation);
			m_Orientation *= Maths::Quaternion::fromEulerAngles(rotation);

		}

		void RenderableObject::scale(Maths::Vector3 scaleFactor)
		{
			m_Mesh->scale(scaleFactor);
			m_Scale += scaleFactor;
		}

		void RenderableObject::move(Maths::Vector3 offset)
		{
			m_Mesh->translate(offset);
			m_Position += offset;
		}

		void RenderableObject::move(Maths::Vector3 direction, float amount)
		{
			move(direction.normalise() * amount);
		}

		void RenderableObject::moveTowards(Maths::Vector3 destination, float amount)
		{
			Maths::Vector3 forward = (destination - m_Position).normalise();

			move(forward * amount);
		}

		void RenderableObject::lookAt(Maths::Vector3 destination)
		{
			Maths::Vector3 forward = (destination - m_Position).normalise();
			Maths::Vector3 up = Maths::Vector3(0, 1, 0); // TODO: A constant up may be the cause of rolling objects (update up to always point "up" from the top of the model)

			float dot = forward.dot(m_Front);

			if (abs(dot - (-1.0f)) < 0.000001f)
			{
				setOrientation(Maths::Quaternion(up.x, up.y, up.z, 3.1415926535897932f));
			}

			else if (abs(dot - (1.0f)) < 0.000001f)
			{
				setOrientation(Maths::Quaternion());
			}
			else
			{
				float angle = acos(dot);
				Maths::Vector3 axis = (m_Front * forward).normalise();

				Maths::Quaternion orientation = Maths::Quaternion::fromAxisAngle(angle, axis);

				setOrientation(orientation.conjugate());
			}
		}
	}
}