#include "FlyCamera.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Cameras
		{
			void FlyCamera::move(Direction direction, float distance)
			{
				switch (direction)
				{
				case Direction::forward:
					m_Position += m_Front * distance;
					break;
				case Direction::backward:
					m_Position -= m_Front * distance;
					break;
				case Direction::right:
					m_Position += (m_Front * m_Up).normalise() * distance;
					break;
				case Direction::left:
					m_Position -= (m_Front * m_Up).normalise() * distance;
					break;
				case Direction::up:
					m_Position += m_Up * distance;
					break;
				case Direction::down:
					m_Position -= m_Up * distance;
					break;
				}
			}

			void FlyCamera::move(Direction direction)
			{
				move(direction, m_DefaultMoveDistance);
			}

			void FlyCamera::move(Maths::Vector3 displacement)
			{
				m_Position += displacement;
			}
		}
	}
}