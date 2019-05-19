#pragma once

#include "../../Logic/Maths/Vector2.h"
#include "../../Graphics/Shaders/Shader.h"
#include "../Buffers/VertexArray.h"
#include "../Buffers/VertexBuffer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace UI
		{
			class UIObject
			{
			public:
				UIObject() {};
				virtual ~UIObject() {};

				virtual void render() {};

				void setShader(Shaders::Shader* shader) { m_Shader = shader; }

			protected:
				Maths::Vector2 m_Position;
				float m_Rotation;
				Shaders::Shader *m_Shader;
				Buffers::VertexArray m_VAO;
				Buffers::VertexBuffer m_VBO = Buffers::VertexBuffer(NULL, sizeof(GLfloat) * 6 * 4, 4, GL_DYNAMIC_DRAW);
			};
		}
	}
}
