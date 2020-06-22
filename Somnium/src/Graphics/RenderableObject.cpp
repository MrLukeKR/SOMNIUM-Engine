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
			scale(1 / m_Scale.x, 1 / m_Scale.y, 1 / m_Scale.z);
			scale(Maths::Vector3(x, y, z));
		}

		void RenderableObject::setOrientation(float x, float y, float z)
		{
			m_Mesh->setOrientation(x, y, z);
		}

		void RenderableObject::rotate(Maths::Vector3 rotation)
		{
			Maths::Vector3 oldPos = m_Position;
			setPosition(0, 0, 0);

			m_Mesh->rotate(rotation);
			m_Orientation += rotation;

			setPosition(oldPos);
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
			Maths::Vector3 direction = Maths::Vector3::dot(m_Position, destination);

			cout << "POSITION: " << m_Position.toString() << "\tDESTINATION: " << destination.toString() << endl;

			m_Mesh->translate(direction * amount);
		}
	}
}