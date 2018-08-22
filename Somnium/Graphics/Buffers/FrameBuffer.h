#pragma once

#include "Buffer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			class FrameBuffer
					: public Buffer
					  {
				public:
					FrameBuffer(unsigned int noOfColourBuffers = 1);
					virtual ~FrameBuffer() { glDeleteFramebuffers(1, &m_BufferID); delete[] m_Attachments;}

					void draw() const;

					inline void bind() const { glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID); }
					inline void unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

				private:
					GLuint m_BufferID = 0;
					GLuint const m_NoOfColourBuffers;
					GLuint* const m_Attachments;
			};
		}
	}
}
