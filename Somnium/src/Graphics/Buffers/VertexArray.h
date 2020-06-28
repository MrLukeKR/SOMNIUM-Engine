#pragma once

#include <vector>
#include "Buffer.h"
#include "VertexBuffer.h"

using namespace std;

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			class VertexArray
			: public Buffer
			{
			public:
				VertexArray();
				~VertexArray();
	
				void addBuffer(VertexBuffer* vertexBuffer, GLuint index, GLuint stride = 0, const GLvoid* offset = 0);

				void draw(unsigned int count) const;

				inline void bind() const { glBindVertexArray(m_ArrayID); }
				inline void unbind() const { glBindVertexArray(0); }
	
			private:
				GLuint m_ArrayID = 0;
				vector<VertexBuffer*> m_Buffers;
			};
		}
	}
}
