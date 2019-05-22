#pragma once

#include "../Window.h"
#include "../Camera.h"
#include "../RenderableObject.h"
#include <queue>
#include <iostream>

namespace Somnium
{
	namespace Graphics
	{
		namespace Renderers
		{
			class Renderer
			{
			public:
				Renderer(const Window& window, Camera& camera)
					: m_Camera(camera), m_Window(window) {};

				virtual ~Renderer() {};

				virtual void submitToQueue(RenderableObject* object) = 0;
				virtual void submitToQueue(std::map<char*, RenderableObject*> objects) = 0;
				virtual void render(bool flushQueue = false) = 0;

				void updateCamera(float deltaTime)
				{
					//Process Keyboard input

					if (m_Window.isKeyPressed(GLFW_KEY_LEFT) || m_Window.isKeyPressed(GLFW_KEY_A))
						m_Camera.move(Camera::Direction::left);
					if (m_Window.isKeyPressed(GLFW_KEY_RIGHT) || m_Window.isKeyPressed(GLFW_KEY_D))
						m_Camera.move(Camera::Direction::right);
					if (m_Window.isKeyPressed(GLFW_KEY_UP) || m_Window.isKeyPressed(GLFW_KEY_W))
					{
						if (m_Window.isKeyPressed(GLFW_KEY_LEFT_CONTROL) || m_Window.isKeyPressed(GLFW_KEY_RIGHT_CONTROL))
							m_Camera.move(Camera::Direction::up);
						else
							m_Camera.move(Camera::Direction::forward);
					}
					if (m_Window.isKeyPressed(GLFW_KEY_DOWN) || m_Window.isKeyPressed(GLFW_KEY_S))
					{
						if (m_Window.isKeyPressed(GLFW_KEY_LEFT_CONTROL) || m_Window.isKeyPressed(GLFW_KEY_RIGHT_CONTROL))
							m_Camera.move(Camera::Direction::down);
						else
							m_Camera.move(Camera::Direction::backward);
					}

					if(m_Window.isKeyPressed(GLFW_KEY_LEFT_SHIFT))
						m_Camera.setSpeedMultiplier(0.2f * deltaTime);
					else
						m_Camera.setSpeedMultiplier(0.1f * deltaTime);
						

					Maths::Vector3 cameraPos = m_Camera.getPosition();
					Maths::Vector3 cameraDeg = m_Camera.getOrientation();

					//Process Mouse Input
					/* Stage 1: Scroll Wheel */

					static int prevXScrollOffset, prevYScrollOffset, xScrollOffset = 0, yScrollOffset = 0;

					prevXScrollOffset = xScrollOffset;
					prevYScrollOffset = yScrollOffset;

					m_Window.getMouseScroll(xScrollOffset, yScrollOffset);

					if (prevYScrollOffset < yScrollOffset)
						m_Camera.offsetFOV(1);
					else if (prevYScrollOffset > yScrollOffset)
						m_Camera.offsetFOV(-1);

					/* Stage 2: X/Y Offset */
					static int mouseX = m_Window.getWidth() / 2, mouseY = m_Window.getHeight() / 2, prevMouseX = m_Window.getWidth() / 2, prevMouseY = m_Window.getHeight() / 2, xOffset, yOffset;
					
					m_Window.getMousePosition(mouseX, mouseY);

					xOffset = mouseX - prevMouseX; //TODO: Some sort of axis inversion option
					yOffset = mouseY - prevMouseY;

					prevMouseX = mouseX;
					prevMouseY = mouseY;

					m_Camera.offsetOrientation(yOffset, xOffset);
				}

			protected:
				Camera& m_Camera;
				const Window& m_Window;
			};
		}
	}
}
