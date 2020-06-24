#include "FlyCamera.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Cameras
		{
			FlyCamera::FlyCamera(const float fieldOfView, const float aspectRatio, const float near, const float far, const bool orthographic, Maths::Vector3 position, Maths::Vector3 orientation):
				m_Position(position), m_Orientation(orientation), m_FieldOfView(fieldOfView), m_AspectRatio(aspectRatio), m_Near(near) , m_Far(far), m_Orthographic(orthographic)
			{
				m_MaxPitch = 269;
				m_MinPitch = 91;

				updateProjection();
				updateView();
			}

			void Camera::setFOV(const float fov)
			{
				if (fov >= m_MinFieldOfView && fov <= m_MaxFieldOfView) m_FieldOfView = fov;
				updateProjection();
			}

			void Camera::updateProjection()
			{
				if(m_Orthographic)
					m_Projection = Maths::Matrix4::orthographic(-m_AspectRatio / 2.0f, m_AspectRatio / 2.0f, -0.5f, 0.5f, m_Near, m_Far);
				else
					m_Projection = Maths::Matrix4::perspective(m_FieldOfView, m_AspectRatio, m_Near, m_Far);
				updateView();
			}

			void Camera::setOrientation(Maths::Vector3& orientation) {
				m_Orientation = clampOrientation(orientation);
			}

			void Camera::move(Direction direction, float distance)
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

			void Camera::move(Maths::Vector3 displacement)
			{
				m_Position += displacement;
			}

			void Camera::updateView()
			{
				m_Direction.x = cos(Maths::toRadians(m_Orientation.x)) * cos(Maths::toRadians(m_Orientation.y));
				m_Direction.y = sin(Maths::toRadians(m_Orientation.x));
				m_Direction.z = cos(Maths::toRadians(m_Orientation.x)) * sin(Maths::toRadians(m_Orientation.y));
			
				m_Front = m_Direction.normalise();

				m_View = Maths::Matrix4::lookAt(m_Position, m_Position + m_Front, m_Up);
			}

			void Camera::updateUI()
			{
	#ifdef ENABLE_DEBUG_CAMERA
				char buffer[1024];

				static UI::UIObject
					*uiCamPos = m_UIObjects.at("CameraPosition"), 
					*uiCamRot = m_UIObjects.at("CameraOrientation"),
					*uiCamFOV = m_UIObjects.at("FieldOfView");

				snprintf(buffer, 1024, "CAM POS [X: %f, Y: %f, Z: %f]", m_Position.x, m_Position.y, m_Position.z);
				((UI::UIText*)uiCamPos)->setText(buffer);
			
				snprintf(buffer, 1024, "CAM ROT [P: %d, Y: %d, R: %d]", (int)(360 + m_Orientation.x) % 360, (int)(360 + -m_Orientation.y) % 360, (int)(360 + m_Orientation.z) % 360);
				((UI::UIText*)uiCamRot)->setText(buffer);

				snprintf(buffer, 1024, "CAM FOV [%d]", m_FieldOfView);
				((UI::UIText*)uiCamFOV)->setText(buffer);
	#endif
			}

			void Camera::drawUI()
			{
				if(m_UIObjects.empty()) return;

				std::map<std::string, UI::UIObject*>::iterator it;

				for (it = m_UIObjects.begin(); it != m_UIObjects.end(); it++)
					it->second->render();
			}
		}
	}
}