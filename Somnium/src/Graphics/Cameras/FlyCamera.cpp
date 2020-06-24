#include "FlyCamera.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Cameras
		{
			FlyCamera::FlyCamera(const float fieldOfView, const float aspectRatio, const float near, const float far, const bool orthographic, Maths::Vector3 position, Maths::Vector3 orientation)
				: Camera(fieldOfView, aspectRatio, near, far, orthographic, position, orientation)
			{
				m_MaxPitch = 269;
				m_MinPitch = 91;

				updateProjection();
				updateView();
			}

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

			void FlyCamera::move(Maths::Vector3 displacement)
			{
				m_Position += displacement;
			}

			void FlyCamera::move(Direction direction) 
			{
				move(direction, m_DefaultMoveDistance * m_Speed);
			}
		}
	}
}