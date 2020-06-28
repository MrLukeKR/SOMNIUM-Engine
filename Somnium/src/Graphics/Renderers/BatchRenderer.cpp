#include "BatchRenderer.h"

#include "../Buffers/IndexBuffer.h"
#include <iostream>

namespace Somnium
{
	namespace Graphics
	{
		namespace Renderers
		{
			BatchRenderer::~BatchRenderer()
			{
				delete m_IBO;
			}

			void BatchRenderer::render(bool flushQueue)
			{
				if (m_CurrentIndex == 0 || m_CurrentVertexCount == 0) return;

				if (m_Mapped)
					endMapping();

				glBindVertexArray(m_VAO); // Bind
				m_IBO->bind();

				glDrawElements(GL_TRIANGLES, m_CurrentIndex, GL_UNSIGNED_SHORT, NULL);

				m_IBO->unbind();
				glBindVertexArray(0); // Unbind

				m_CurrentIndex = 0;
				m_CurrentVertexCount = 0;
			}

			void BatchRenderer::init()
			{
				glGenVertexArrays(1, &m_VAO);
				glGenBuffers(1, &m_VBO);

				glBindVertexArray(m_VAO);
				glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
				glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);
				
				glEnableVertexAttribArray(SHADER_POSITION_INDEX);
				glEnableVertexAttribArray(SHADER_NORMAL_INDEX);
				glEnableVertexAttribArray(SHADER_TEXTURE_COORDINATE_INDEX);
				
				glVertexAttribPointer(SHADER_POSITION_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
				glVertexAttribPointer(SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*) sizeof(Maths::Vector3));
				glVertexAttribPointer(SHADER_TEXTURE_COORDINATE_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(2 * sizeof(Maths::Vector3)));

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				unsigned int offset = 0;

				std::vector<GLushort> indices;

				for (unsigned int i = 0; i < INDEX_AMOUNT; i += 6) //TODO: Make the number variable
				{
					for (unsigned int ind = 0; ind <= 2; ind++)
						indices.push_back(offset + ind);
					for (unsigned int ind = 2; ind <= 4; ind++)
						indices.push_back(offset + (ind % 4));

					offset += 4;
				}

				m_IBO = new Buffers::IndexBuffer(indices, INDEX_AMOUNT);

				glBindVertexArray(0);
			}

			void BatchRenderer::beginMapping()
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
#ifndef WEB_BUILD
				m_VertexDataBuffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
#else
				//TODO: glSubData version
#endif
				m_Mapped = true;
			}

			void BatchRenderer::submitToQueue(RenderableObject* object)
			{
				if (m_CurrentVertexCount == 0 && !m_Mapped)
					beginMapping();

				const std::vector<Maths::Vector3>& test = object->getMesh()->getVertexData();

				if (m_CurrentVertexCount + test.size() >= MAX_VERTICES)
				{
					cerr << "ERROR: BATCH FULL - CANNOT ADD MORE VERTICES!" << endl;
					return; //Too many vertices
				}

				for (Maths::Vector3 vertex : test)
				{
					(m_VertexDataBuffer++)->position = vertex;
				}

				m_CurrentVertexCount += test.size();
				cout << sizeof(Vertex) << endl;
				m_CurrentIndex += test.size() * 8;
			}

			void BatchRenderer::endMapping()
			{
				glUnmapBuffer(GL_ARRAY_BUFFER);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				m_Mapped = false;
			}
		}
	}
}
