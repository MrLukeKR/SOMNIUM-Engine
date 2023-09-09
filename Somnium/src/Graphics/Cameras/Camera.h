#pragma once

#include "../../Logic/Maths/Maths.h"
#include "../UI/UIObject.h"
#include "../UI/UIText.h"
#include "../UI/UIImage.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Cameras
		{
			class Camera
			{
			/* Methods */
			public:				
				virtual ~Camera() {};

				enum class Direction { forward, backward, left, right, up, down };

				const Maths::Matrix4& getView() const { return m_View; }
				const Maths::Vector3& getUp() const { return m_Up; }
				const Maths::Vector3& getForward() const { return m_Front; }

				const Maths::Matrix4& getProjection() const { return m_Projection; }
				float getFOV() const { return m_FieldOfView; }
				const Maths::Vector3& getPosition() const { return m_Position; }
				const Maths::Vector3& getOrientation() const { return m_Orientation; }

				void lookAt(Maths::Vector3 destination);

				inline Maths::Vector3 clampOrientation(Maths::Vector3 orientation) {
					Maths::Vector3 cleanOrientation;

					cleanOrientation.x = fmod(orientation.x, 360.f);
					cleanOrientation.y = fmod(orientation.y, 360.f);
					cleanOrientation.z = fmod(orientation.z, 360.f);

					if (m_MinPitch > -1 && m_MaxPitch > -1) cleanOrientation.x = Maths::clamp(cleanOrientation.x, m_MinPitch, m_MaxPitch);
					if (m_MinYaw > -1 && m_MaxYaw > -1)		cleanOrientation.y = Maths::clamp(cleanOrientation.y, m_MinYaw, m_MaxYaw);
					if (m_MinRoll > -1 && m_MaxRoll > -1)	cleanOrientation.z = Maths::clamp(cleanOrientation.z, m_MinRoll, m_MaxRoll);

					return cleanOrientation;
				}

				void setOrientation(Maths::Vector3& orientation)
				{
					m_Orientation = clampOrientation(orientation);
				}

				void setOrientation(const float &pitchAngle, float const &yawAngle, const float &rollAngle = 0) { m_Orientation = Maths::Vector3(pitchAngle, yawAngle, rollAngle); }
				void offsetOrientation(const float &pitchAngle, float const &yawAngle, const float &rollAngle = 0) 
				{
					m_Orientation += Maths::Vector3(pitchAngle, yawAngle, rollAngle) * m_Sensitivity; 
					m_Orientation = clampOrientation(m_Orientation);
					updateView(); 
				}

				void setFOV(const float fov) {
					if (fov >= m_MinFieldOfView && fov <= m_MaxFieldOfView) m_FieldOfView = fov;
					updateProjection();
				}

				void setPitch(float const &angle);
				void setYaw(float const &angle);
				void setRoll(float const &angle);
				void setPosition();
				void setSpeedMultiplier(float multiplier) { m_Speed = m_BaseSpeed * multiplier; }

				void offsetFOV(const float offset) { setFOV(m_FieldOfView + offset); }

				virtual void move(Direction direction) = 0;
				virtual void move(Direction direction, float offset) = 0;
				virtual void move(Maths::Vector3 displacement) = 0;
			
				/* UI Controls */
			
				void addUIObject(std::string key, UI::UIObject* object) { m_UIObjects.insert(std::pair<std::string, UI::UIObject*>(key, object)); }
				void setUIText(std::string key, std::string text) { ((UI::UIText*) m_UIObjects.at(key))->setText(text.c_str()); }

				void removeUIObject(std::string key) { m_UIObjects.erase(key); }

				void updateUI() {
#ifdef ENABLE_DEBUG_CAMERA
					char buffer[1024];

					static UI::UIObject
						* uiCamPos = m_UIObjects.at("CameraPosition"),
						* uiCamRot = m_UIObjects.at("CameraOrientation"),
						* uiCamFOV = m_UIObjects.at("FieldOfView");

					snprintf(buffer, 1024, "CAM POS [X: %f, Y: %f, Z: %f]", m_Position.x, m_Position.y, m_Position.z);
					((UI::UIText*)uiCamPos)->setText(buffer);

					snprintf(buffer, 1024, "CAM ROT [P: %d, Y: %d, R: %d]", (int)(360 + m_Orientation.x) % 360, (int)(360 + -m_Orientation.y) % 360, (int)(360 + m_Orientation.z) % 360);
					((UI::UIText*)uiCamRot)->setText(buffer);

					snprintf(buffer, 1024, "CAM FOV [%d]", m_FieldOfView);
					((UI::UIText*)uiCamFOV)->setText(buffer);
#endif

				}

				void drawUI() {
					if (m_UIObjects.empty()) return;

					std::map<std::string, UI::UIObject*>::iterator it;

					for (it = m_UIObjects.begin(); it != m_UIObjects.end(); it++)
						it->second->render();
				}

				void clearUI() {};

			protected:
				Camera(const float fieldOfView, const float aspectRatio = 16.f / 9.f, const float near = 0.1f, const float far = 0.1f, const bool orthographic = false, Maths::Vector3 position = Maths::Vector3(), Maths::Vector3 orientation = Maths::Vector3())
				: m_FieldOfView(fieldOfView), m_AspectRatio(aspectRatio), m_Near(near), m_Far(far), m_Orthographic(orthographic), m_Position(position), m_Orientation(orientation) 
				{
					m_Orientation.y = -m_Orientation.y;

					updateProjection();
					updateView();
				};

				void updateView() {
					m_Direction.x = cos(Maths::toRadians(m_Orientation.x)) * cos(Maths::toRadians(m_Orientation.y));
					m_Direction.y = sin(Maths::toRadians(m_Orientation.x));
					m_Direction.z = cos(Maths::toRadians(m_Orientation.x)) * sin(Maths::toRadians(m_Orientation.y));

					m_Front = m_Direction.normalise();

					m_View = Maths::Matrix4::lookAt(m_Position, m_Position + m_Front, m_Up);
				}
				void updateProjection()
				{
					if (m_Orthographic)
						m_Projection = Maths::Matrix4::orthographic(-m_AspectRatio / 2.0f, m_AspectRatio / 2.0f, -0.5f, 0.5f, m_Near, m_Far);
					else
						m_Projection = Maths::Matrix4::perspective(m_FieldOfView, m_AspectRatio, m_Near, m_Far);
					updateView();
				};

				private:
					Camera();
			/* Variables */
			public:

			protected:
				unsigned int m_FieldOfView = 45,
					m_MaxFieldOfView = 179,
					m_MinFieldOfView = 1;

				float
					m_AspectRatio,
					m_Near = 0.1f,
					m_Far = 100.f,
					m_Sensitivity = 0.05f,
					m_BaseSpeed = 1,
					m_Speed = m_BaseSpeed,
					m_MaxPitch = -1,
					m_MinPitch = -1,
					m_MaxYaw = -1,
					m_MinYaw = -1,
					m_MaxRoll = -1,
					m_MinRoll = -1;

				Maths::Matrix4 m_Projection;
				Maths::Vector3 m_Position, m_Orientation, m_Target = Maths::Vector3(0, 0, -1);
				Maths::Vector3 m_Direction = (m_Position - m_Target).normalise();
			
				Maths::Vector3
					m_Up = Maths::Vector3(0, 1, 0),
					m_Front = Maths::Vector3(0, 0, -1);

				bool m_Orthographic = false;

				Maths::Matrix4 m_View; //The finalized representation of the camera's viewpoint

				std::map<std::string, UI::UIObject*> m_UIObjects;
			};
		}
	}
}
