#pragma once

#include "../../Logic/Maths/Vector3.h"
#include "../../Graphics/Buffers/VertexArray.h"
#include "../../Graphics/Buffers/VertexBuffer.h"
#include "../../Graphics/RenderableObject.h"
#include "../../Graphics/Shaders/Shader.h"

namespace Somnium
{
	namespace Utilities
	{
		namespace Debug
		{
			namespace Tools
			{
				class ReferenceGrid
				{
					public:
						ReferenceGrid(float divisionSize, Maths::Vector3 gridSize, Graphics::Shaders::Shader& shader)
						: m_DivisionSize(divisionSize), m_Shader(shader), m_GridSize(gridSize)
						{
							init();

							m_VAO.bind();
							m_VBO->bind();

							m_VAO.addBuffer(m_VBO, SHADER_POSITION_INDEX);

							m_VBO->unbind();
							m_VAO.unbind();
						}

						void show() { m_Show = true; }
						void hide() { m_Show = false; }
						void toggle() { m_Show = !m_Show; }
						void setGridSize(float size);
						void setDivision(float size);

						void draw();

					private:
						inline void updateSquares()
						{
							m_xSquares = floor((m_GridSize.x / m_DivisionSize));
							m_ySquares = floor((m_GridSize.y / m_DivisionSize));
						}

						void init();

					private:
						float m_DivisionSize;
						int m_xSquares, m_ySquares;
						Graphics::Shaders::Shader& m_Shader;
						std::vector<GLfloat> m_VertexData;
						Maths::Vector3 m_GridSize;
						Graphics::Buffers::VertexArray m_VAO;
						Graphics::Buffers::VertexBuffer* m_VBO;
						bool m_Show;
				};
			}
		}
	}
}
