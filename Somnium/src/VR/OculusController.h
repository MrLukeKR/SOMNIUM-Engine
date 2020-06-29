#pragma once

#pragma comment(lib, "winmm.lib")
#include "../../Dependencies/oculus/LibOVR/include/OVR_CAPI.h"
#include <string>

namespace Somnium
{
	namespace VR
	{
		class OculusController
		{
		public:
			OculusController();
			~OculusController();

			std::string getSDKInformation() const;
			void printHMDInformation() const;

		private:
			ovrSession m_Session;
			ovrGraphicsLuid m_LUID;
			ovrHmdDesc m_Description;
			ovrSizei m_Resolution;
			ovrResult m_Status;
		};
	}
}