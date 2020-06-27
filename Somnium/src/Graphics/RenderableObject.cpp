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
			m_Mesh->rotate(- m_Orientation);
			m_Orientation = Maths::Vector3(x, y, z);
			m_Mesh->rotate(Maths::Vector3(x, y, z));
		}

		void RenderableObject::rotate(Maths::Vector3 rotation)
		{

			m_Mesh->rotate(rotation);
			m_Orientation += rotation;

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
			Maths::Vector3 delta = (destination - m_Position).normalise();

			move(delta * amount);
		}

		void RenderableObject::lookAt(Maths::Vector3 destination)
		{
			Maths::Vector3 delta = (destination - m_Position).normalise();

			float cosA = delta.dot(m_Front);

			float angle = Maths::clamp(cosA, -1.f, 1.f);
			angle = Maths::toDegrees(acos(cosA));

			Maths::Vector3 axis = (m_Front * delta).normalise();
			
			axis.x = -axis.x;

			Maths::Vector3 orientation = axis * angle;

			setOrientation(orientation);
		}
	}
}