#pragma once

#define SHADER_POSITION_INDEX 0
#define SHADER_NORMAL_INDEX 1
#define SHADER_TEXTURE_COORDINATE_INDEX 2

#ifdef WEB_BUILD 
	#define GLFW_INCLUDE_ES3
#else 
	#include <glew.h> 
#endif
#include "../../Maths/Maths.h"

#ifdef WEB_BUILD
	#define CHAR char
	#define UINT unsigned int
	#define INT int
#else
	#define CHAR GLchar
	#define UINT GLuint
	#define INT GLint
#endif

namespace Somnium {
	namespace Graphics {
		namespace Shaders
		{
		class Shader
		{
		public:
			Shader(const char* vertexFilePath, const char* fragmentFilePath);
			~Shader();

			void setInt(const CHAR*, int value);
			void setFloat(const CHAR*, float value);
			void setVector2(const CHAR*, const Maths::Vector2&);
			void setVector3(const CHAR*, const Maths::Vector3&);
			void setVector4(const CHAR*, const Maths::Vector4&);
			void setMatrix4(const CHAR*, const Maths::Matrix4&);

			void enable() const;
			void disable() const;

			UINT getID() const { return m_ShaderID; };

		private:
			UINT load();
			INT getUniformLocation(const CHAR*);

		private:
			UINT m_ShaderID;
			const char *m_VertexFilePath, *m_FragmentFilePath;
		};
	}
}
}
