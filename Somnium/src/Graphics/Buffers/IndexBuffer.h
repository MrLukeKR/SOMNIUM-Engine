#pragma once

#include "Buffer.h"
#include <vector>

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			class IndexBuffer
				: public Buffer
			{
			public:
				IndexBuffer(GLushort* indices, size_t numberOfIndices);
				IndexBuffer(std::vector<GLushort> data, size_t count) 
					: IndexBuffer(data.data(), count) {};
				IndexBuffer(std::vector<GLushort> data)
					: IndexBuffer(data.data(), data.size()) {};
				
				~IndexBuffer() { glDeleteBuffers(1, &m_BufferID); }

				inline unsigned int getCount() const { return m_Count; }
				inline void bind()   const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID); }
				inline void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

			private:
				GLuint m_BufferID = 0;
				GLuint m_Count = 0;
			};
		}
	}
}
