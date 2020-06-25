#include "FirstPersonCamera.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Cameras
		{
			FirstPersonCamera::FirstPersonCamera(const float fieldOfView, const float aspectRatio, const float near, const float far, const bool orthographic, Maths::Vector3 position, Maths::Vector3 orientation)
				: Camera(fieldOfView, aspectRatio, near, far, orthographic, position, orientation)
			{
				m_MaxPitch = 269;
				m_MinPitch = 91;

				updateProjection();
				updateView();
			}

			void FirstPersonCamera::move(Direction direction, float distance)
			{
				Maths::Vector3 front2d = m_Front;
				front2d.y = 0;

				switch (direction)
				{
				case Direction::forward:
					m_Position += front2d * distance;
					break;
				case Direction::backward:
					m_Position -= front2d * distance;
					break;
				case Direction::right:
					m_Position += (front2d * m_Up).normalise() * distance;
					break;
				case Direction::left:
					m_Position -= (front2d * m_Up).normalise() * distance;
					break;
				//TODO: Allow for jumping
				}
			}

			void FirstPersonCamera::move(Maths::Vector3 displacement)
			{
				m_Position += displacement;
			}

			void FirstPersonCamera::move(Direction direction)
			{
				move(direction, m_DefaultMoveDistance * m_Speed);
			}
		}
	}
}