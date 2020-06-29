#pragma once

#ifdef WEB_BUILD 
	#define GLFW_INCLUDE_ES3
#else 
	#include <glew.h> 
#endif
#include <glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

#ifdef _WIN32
	#include "../VR/OculusController.h"
#endif

namespace Somnium
{
	namespace Graphics
	{
		extern void keyCallback(GLFWwindow*, int, int, int, int);
		extern void mouseButtonCallback(GLFWwindow*, int, int, int);
		extern void cursorPositionCallback(GLFWwindow*, double, double);
		extern void mouseScrollCallback(GLFWwindow*, double, double);

		class Window
		{
		public:
			Window(const char*, unsigned int, unsigned int, bool fullScreen);
			~Window();

			void clear(void)  const;
			void update(void) const;

			bool isClosed(void) const { return glfwWindowShouldClose(m_Window); }

			inline int getWidth(void) const { return m_Width; }
			inline int getHeight(void) const { return m_Height; }
			inline float getAspectRatio(void) const { return m_Width / (float)m_Height;  }
			const inline FT_Library& getFreeTypeInstance() const { return m_FreeType; }

			bool isKeyPressed(unsigned int) const;
			bool isMouseButtonPressed(unsigned int) const;
			void getMousePosition(int& x, int& y) const;
			void getMouseScroll(int& xOffset, int& yOffset) const;

			friend void resize(GLFWwindow*, int, int);

		private:
			void applySettings();
			bool init(void);

			void printDebugTitle(std::string title);

			friend void keyCallback(GLFWwindow*, int, int, int, int);
			friend void mouseButtonCallback(GLFWwindow*, int, int, int);
			friend void mouseScrollCallback(GLFWwindow*, double, double);
			friend void cursorPositionCallback(GLFWwindow*, double, double);
			friend void errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

		private:
			friend struct GLFWwindow;

			FT_Library m_FreeType;

			const char *m_Title;
			unsigned int m_Width, m_Height;
			GLFWwindow *m_Window = nullptr;

			bool m_FullScreen;
			bool m_Keys[GLFW_KEY_LAST] = { false };
			bool m_MouseButtons[GLFW_MOUSE_BUTTON_LAST] = { false };
			double m_MouseX = 0.0, m_MouseY = 0.0;
			double m_MouseScrollXOffset = 0.0, m_MouseScrollYOffset = 0.0;
		};
	}
}
