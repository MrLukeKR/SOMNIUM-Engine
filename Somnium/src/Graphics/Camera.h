#pragma once

#include "../Logic/Maths/Maths.h"
#include "UI/UIObject.h"
#include "UI/UIText.h"
#include "UI/UIImage.h"

namespace Somnium
{
	namespace Graphics
	{
		class Camera
		{
		/* Methods */
		public:
			Camera(const float fieldOfView, const float aspectRatio, const float near = 0.1f, const float far = 0.1f, const bool orthographic = false, Maths::Vector3 position = Maths::Vector3(), Maths::Vector3 orientation = Maths::Vector3());
			~Camera() {};

			enum Direction{ forward, backward, left, right, up, down };

			const Maths::Matrix4& getView() const { return m_View; };
			const Maths::Matrix4& getProjection() const { return m_Projection; }
			float getFOV() const { return m_FieldOfView; }
			const Maths::Vector3& getPosition() const { return m_Position; };
			const Maths::Vector3& getOrientation() const { return m_Orientation; };

			void lookAt();
			void setOrientation(Maths::Vector3 &orientation) { m_Orientation = orientation; };
			void setOrientation(const float &pitchAngle, float const &yawAngle, const float &rollAngle = 0) { m_Orientation = Maths::Vector3(pitchAngle, yawAngle, rollAngle); }
			void offsetOrientation(const float &pitchAngle, float const &yawAngle, const float &rollAngle = 0) 
			{
				m_Orientation += Maths::Vector3(pitchAngle, yawAngle, rollAngle) * m_Sensitivity; 
				updateView(); 
			}
			void setFOV(const float fov);
			void setPitch(float const &angle);
			void setYaw(float const &angle);
			void setRoll(float const &angle);
			void setPosition();
			void setSpeedMultiplier(float multiplier) { m_Speed = m_BaseSpeed * multiplier; }

			void offsetFOV(const float offset) { setFOV(m_FieldOfView + offset); }

			void move(Direction direction) { move(direction, 0.01f * m_Speed); }
			void move(Direction direction, float offset);
			void move(Maths::Vector3 displacement);
			
			/* UI Controls */
			
			void addUIObject(std::string key, UI::UIObject* object) { m_UIObjects.insert(std::pair<std::string, UI::UIObject*>(key, object)); }
			void removeUIObject();

			void updateUI();
			void drawUI();
			void clearUI() {};

		private:
			void updateView();
			void updateProjection();

		/* Variables */
		public:

		private:
			Maths::Matrix4 m_Projection;
			Maths::Vector3 m_Position, m_Orientation, m_Target = Maths::Vector3(0, 0, -1);
			Maths::Vector3 m_Direction = (m_Position - m_Target).normalise();
			
			Maths::Vector3
				m_Up = Maths::Vector3(0, 1, 0),
				m_Front = Maths::Vector3(0, 0, -1);

			unsigned int m_FieldOfView = 45;
			float
				m_AspectRatio,
				m_Near = 0.1f,
				m_Far = 100.f,
				m_Sensitivity = 0.05f,
				m_BaseSpeed = 1,
				m_Speed = m_BaseSpeed;
			bool m_Orthographic = false;

			Maths::Matrix4 m_View; //The finalized representation of the camera's viewpoint

			std::map<std::string, UI::UIObject*> m_UIObjects;
		};
	}
}
