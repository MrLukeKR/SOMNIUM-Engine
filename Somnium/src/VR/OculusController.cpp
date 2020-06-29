#include "OculusController.h"

namespace Somnium
{
	namespace VR
	{
		OculusController::OculusController()
		{
			ovrResult result = ovr_Initialize(nullptr);
			
			if (OVR_FAILURE(result))
				return;

			result = ovr_Create(&m_Session, &m_LUID);
			if (OVR_FAILURE(result))
			{
				ovr_Shutdown();
				return;
			}
				
			m_Description = ovr_GetHmdDesc(m_Session);
			m_Resolution = m_Description.Resolution;
		}

		OculusController::~OculusController()
		{
			ovr_Destroy(m_Session);
			ovr_Shutdown();
		}
	}
}