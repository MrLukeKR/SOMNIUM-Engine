#include "Camera.h"

namespace Somnium
{
	namespace Graphics
	{
		Camera::Camera(const float fieldOfView, const float aspectRatio, const float near, const float far, const bool orthographic, Maths::Vector3 position, Maths::Vector3 orientation):
			m_Position(position), m_Orientation(orientation), m_FieldOfView(fieldOfView), m_Near(near), m_Far(far), m_Orthographic(orthographic), m_AspectRatio(aspectRatio)
		{
			updateProjection();
			updateView();
		}

		void Camera::setFOV(const float fov)
		{
			if (fov >= 1.f && fov <= 45.f) m_FieldOfView = fov;
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

		void Camera::move(Maths::Vector3 displacement)
		{
			m_Position -= displacement; //We're not moving the camera Forward/Backward, we're moving the whole scene Backward/Forward, so have to negate the displacement
			m_View *= Maths::Matrix4::translation(-displacement);
		}

		void Camera::updateView()
		{
			m_View = Maths::Matrix4::translation(m_Position) * //TODO: Include orientation here
			Maths::Matrix4::rotationX(m_Orientation.x) *
				Maths::Matrix4::rotationY(m_Orientation.y) *
				Maths::Matrix4::rotationZ(m_Orientation.z);
		}

		void Camera::updateUI()
		{
#if ENABLE_DEBUG_CAMERA
			char buffer[1024];

			static UI::UIObject
				*uiCamPos = m_UIObjects.at("CameraPosition"), 
				*uiCamRot = m_UIObjects.at("CameraOrientation"),
				*uiCamFOV = m_UIObjects.at("FieldOfView");

			snprintf(buffer, 1024, "CAM POS [X: %f, Y: %f, Z: %f]", -m_Position.x, -m_Position.y, m_Position.z);
			((UI::UIText*)uiCamPos)->setText(buffer);
			
			snprintf(buffer, 1024, "CAM ROT [P: %f, Y: %f, R: %f]", m_Orientation.x, -m_Orientation.y, m_Orientation.z);
			((UI::UIText*)uiCamRot)->setText(buffer);

			snprintf(buffer, 1024, "CAM FOV [%d]", m_FieldOfView);
			((UI::UIText*)uiCamFOV)->setText(buffer);
			
			//printf("CURSOR POSITION - X: %d, Y: %d\r\n", mouseX, mouseY);
			//printf("CURSOR OFFSET - X: %d, Y: %d\r\n", xOffset, yOffset);
#endif
		}

		void Camera::drawUI()
		{
			std::map<std::string, UI::UIObject*>::iterator it;

			for (it = m_UIObjects.begin(); it != m_UIObjects.end(); it++)
				it->second->render();
		}
	}
}
