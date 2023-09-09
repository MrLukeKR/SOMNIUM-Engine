#ifdef _WIN32
	#pragma once

	#pragma comment(lib, "winmm.lib")
	#include "../../Dependencies/oculus/LibOVR/include/OVR_CAPI_GL.h"
	#include <string>

	namespace Somnium
	{
		namespace VR
		{
			class OculusController
			{
			public:
				static OculusController* init();
				OculusController();
				~OculusController();

				std::string getSDKInformation() const;
				void printHMDInformation() const;
				ovrTrackingState getTrackingState() const;

				static OculusController* getInstance() { return instance; }

			protected:
				static OculusController* instance;

			private:
				ovrSession m_Session;
				ovrGraphicsLuid m_LUID;
				ovrHmdDesc m_Description;
				ovrSizei m_Resolution;
				ovrResult m_Status;
			};
		}
	}
#endif