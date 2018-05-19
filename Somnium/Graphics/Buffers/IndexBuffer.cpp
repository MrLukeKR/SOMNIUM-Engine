#include "IndexBuffer.h"

namespace LKREngine
{
	namespace Graphics
	{
		IndexBuffer::IndexBuffer(GLushort* data, GLsizei count)
			:m_Count(count)
		{
			glGenBuffers(1, &m_BufferID);
			Bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
			Unbind();
		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &m_BufferID);
		}

		void IndexBuffer::Bind() const 
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		}
		
		void IndexBuffer::Unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}