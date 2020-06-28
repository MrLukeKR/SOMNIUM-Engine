#include "VertexArray.h"

#include <iostream>

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			VertexArray::VertexArray() { glGenVertexArrays(1, &m_ArrayID); }

			VertexArray::~VertexArray()
			{
				for (VertexBuffer* buffer : m_Buffers) delete buffer;
				glDeleteVertexArrays(1, &m_ArrayID);
			}

			void VertexArray::addBuffer(VertexBuffer* buffer, GLuint index, GLuint stride, const GLvoid* offset)
			{
				bind();
				buffer->bind();

				glEnableVertexAttribArray(index);

				glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, stride, offset);

				buffer->unbind();
				unbind();

				m_Buffers.push_back(buffer);
			}

			void VertexArray::draw(unsigned int amount) const
			{
				glDrawElements(GL_TRIANGLES, amount, GL_UNSIGNED_SHORT, nullptr);
			}
		}
	}
}
