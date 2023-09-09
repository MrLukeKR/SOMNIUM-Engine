#ifdef _WIN32
	#include "OculusTextureBuffer.h"

namespace Somnium
{
	namespace VR
	{
		OculusTextureBuffer::OculusTextureBuffer(ovrSession session, OVR::Sizei size, int sampleCount) : 
			m_Session(session), 
			m_ColorTextureChain(nullptr),
			m_DepthTextureChain(nullptr),
			m_fboID(0),
			m_TexSize(0, 0)
		{
			int length = 0;

			m_TextureSwapChainDesc.Type = ovrTexture_2D;
			m_TextureSwapChainDesc.ArraySize = 1;
			m_TextureSwapChainDesc.Width = size.w;
			m_TextureSwapChainDesc.Height = size.h;
			m_TextureSwapChainDesc.MipLevels = 1;
			m_TextureSwapChainDesc.Format = OVR_FORMAT_R8G8B8A8_UNORM_SRGB;
			m_TextureSwapChainDesc.SampleCount = sampleCount;
			m_TextureSwapChainDesc.StaticImage = ovrFalse;

			for (int chain = 0; chain < 2; ++chain)
			{
				if (chain == 1) m_TextureSwapChainDesc.Format = OVR_FORMAT_D32_FLOAT;

				m_Status = ovr_CreateTextureSwapChainGL(m_Session, &m_TextureSwapChainDesc, chain == 0 ? &m_ColorTextureChain : &m_DepthTextureChain);
				ovr_GetTextureSwapChainLength(m_Session, chain == 0 ? m_ColorTextureChain : m_DepthTextureChain, &length);

				if (OVR_SUCCESS(m_Status)) {
					for (int i = 0; i < length; ++i) {
						GLuint chainTexId;
						ovr_GetTextureSwapChainBufferGL(m_Session, m_ColorTextureChain, i, &chainTexId);
						glBindTexture(GL_TEXTURE_2D, chainTexId);

						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					}
				}
			}

			glGenFramebuffers(1, &m_fboID);
		}

		OculusTextureBuffer::~OculusTextureBuffer() {
			if (m_ColorTextureChain) {
				ovr_DestroyTextureSwapChain(m_Session, m_ColorTextureChain);
				m_ColorTextureChain = nullptr;
			}

			if (m_DepthTextureChain) {
				ovr_DestroyTextureSwapChain(m_Session, m_DepthTextureChain);
				m_DepthTextureChain = nullptr;
			}

			if (m_fboID) {
				glDeleteFramebuffers(1, &m_fboID);
				m_fboID = 0;
			}
		}

		OVR::Sizei OculusTextureBuffer::getSize() const {
			return m_TexSize;
		}
	}
}
#endif