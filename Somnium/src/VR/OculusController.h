#pragma once

#include "../../Dependencies/oculus/LibOVR/include/OVR_CAPI.h"

namespace Somnium
{
	namespace VR
	{
		class OculusController
		{
		public:
			OculusController();
			~OculusController();

		private:
			ovrSession m_Session;
			ovrGraphicsLuid m_LUID;
			ovrHmdDesc m_Description;
			ovrSizei m_Resolution;
		};
	}
}