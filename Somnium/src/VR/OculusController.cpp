#ifdef _WIN32
	#include "OculusController.h"
	#include <iostream>
	#include <glew.h>

	namespace Somnium
	{
		namespace VR
		{
			OculusController* OculusController::instance;

			OculusController* OculusController::init() {
				instance = new OculusController();
				return instance;
			}

			OculusController::OculusController()
			{
				m_Status = ovr_Initialize(nullptr);
			
				if (OVR_FAILURE(m_Status)) {
					std::cerr << "Failed to initialise Oculus device" << std::endl;
					return;
				}

				m_Status = ovr_Create(&m_Session, &m_LUID);
				if (OVR_FAILURE(m_Status))
				{
					std::cerr << "Failed to initialise LibOVR" << std::endl;
					ovr_Shutdown();
					return;
				}
				
				m_Description = ovr_GetHmdDesc(m_Session);
			
				m_Resolution = m_Description.Resolution;

				instance = this;
			}

			ovrTrackingState OculusController::getTrackingState() const {
				ovrTrackingState ts = ovr_GetTrackingState(m_Session, ovr_GetTimeInSeconds(), ovrTrue);

				if (!ts.StatusFlags | !(ovrStatus_OrientationTracked | ovrStatus_PositionTracked)) {
					std::cerr << "Orientation/Position could not be obtained!" << std::endl;
				}
				return ts;
			}

			std::string OculusController::getSDKInformation() const
			{
				return OVR_VERSION_STRING;
			}

			void OculusController::printHMDInformation() const
			{
				if (OVR_FAILURE(m_Status)) {
					std::cerr << "Could not print HMD information" << std::endl;
					return;
				}

				std::cout << "Connected HMD Information:" << std::endl;
				std::cout << "\tProduct: " << " " << m_Description.ProductName << " by " << m_Description.Manufacturer << " [" << m_Description.SerialNumber << ']' << std::endl;
				std::cout << "\tFirmware Version: " << m_Description.FirmwareMajor << '.' << m_Description.FirmwareMinor << std::endl;
				std::cout << "\tResolution: " << m_Description.Resolution.w << "x" << m_Description.Resolution.h << std::endl;
			}

			OculusController::~OculusController()
			{
				ovr_Destroy(m_Session);
				ovr_Shutdown();
			}
		}
	}
#endif