#include "IndexBuffer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			IndexBuffer::IndexBuffer(GLushort* data, size_t count)
				:m_Count(count)
			{
				glGenBuffers(1, &m_BufferID);
				bind();
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
				unbind();
			}

			IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_BufferID); }

			void IndexBuffer::bind()   const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID); }
			void IndexBuffer::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
		}
	}
}