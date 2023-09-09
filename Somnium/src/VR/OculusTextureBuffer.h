#ifdef _WIN32
#pragma once

#pragma comment(lib, "winmm.lib")
#include "../../Dependencies/oculus/LibOVR/include/OVR_CAPI_GL.h"
#include "../../Dependencies/oculus/LibOVR/include/Extras/OVR_Math.h"
#include <glew.h>

namespace Somnium
{
	namespace VR
	{
		struct OculusTextureBuffer
		{
		public:
			OculusTextureBuffer(ovrSession session, OVR::Sizei size, int sampleCount);
			~OculusTextureBuffer();

			OVR::Sizei getSize() const;

		private:
			GLuint m_fboID = 0;
			ovrSession m_Session;
			ovrTextureSwapChain m_ColorTextureChain = {};
			ovrTextureSwapChain m_DepthTextureChain = {};
			ovrTextureSwapChainDesc m_TextureSwapChainDesc;
			ovrResult m_Status;
			OVR::Sizei m_TexSize;
		};
	}
}
#endif