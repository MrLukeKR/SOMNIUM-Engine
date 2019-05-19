#pragma once

#include <iostream>
#include "../Graphics/UI/UIText.h"
#include "../Graphics/Font.h"
#include "../Graphics/Shaders/Shader.h"
#include "../Utilities/FrameRateUtilities.h"
#include "../Graphics/Camera.h"

namespace Somnium
{
	namespace Utilities
	{
		namespace Debug
		{
			Graphics::UI::UIText *fpsCount, *camPos, *camRot, *camFOV, *engName, *engVer;
			Tools::ReferenceGrid* referenceGrid;
			Graphics::Shaders::Shader* referenceGridShader;
			Graphics::Camera* mainCamera;

			void printWelcomeMessage()
			{
				std::cout << "SOMNIUM by LUMACAL Software Group - Built " << __TIMESTAMP__ << std::endl;
				std::cout << "Please file any bug reports at www.GitHub.com/LUMACAL/Somnium-Engine/issues/new" << std::endl << std::endl;
			}

			void initialiseReferenceGrid(Graphics::Shaders::Shader* gridShader, const float& divisionSize, const Maths::Vector3& gridSize)
			{
				referenceGridShader = gridShader;
				 referenceGrid = new Tools::ReferenceGrid(divisionSize, gridSize, *gridShader);
			}

			void drawReferenceGrid()
			{
				referenceGridShader->enable();
				referenceGridShader->setMatrix4("projectionMatrix", mainCamera->getProjection());
				referenceGridShader->setMatrix4("viewMatrix", mainCamera->getView());
				referenceGrid->draw();
			}

			void initialiseDebugCamera(const unsigned int& windowWidth, const unsigned int& windowHeight, Graphics::Camera* camera, Graphics::Font* font, Graphics::Shaders::Shader* textShader)
			{
				mainCamera = camera;

				fpsCount = new Graphics::UI::UIText("FPS", font, Maths::Vector2(0, windowHeight - 25), textShader);
				camPos = new Graphics::UI::UIText("CAM POS", font, Maths::Vector2(0, windowHeight - 50), textShader);
				camRot = new Graphics::UI::UIText("CAM ROT", font, Maths::Vector2(0, windowHeight - 75), textShader);
				camFOV = new Graphics::UI::UIText("CAM FOV", font, Maths::Vector2(0, windowHeight - 100), textShader);
				engName = new Graphics::UI::UIText("SOMNIUM ENGINE", font, Maths::Vector2(windowWidth - 225, windowHeight - 25), textShader);
				engVer = new Graphics::UI::UIText("DEVELOPMENT BUILD", font, Maths::Vector2(windowWidth - 270, windowHeight - 50), textShader);

				camPos->setScale(0.5f);
				camRot->setScale(0.5f);
				camFOV->setScale(0.5f);
				engName->setScale(0.5f);
				engVer->setScale(0.5f);
				fpsCount->setScale(0.5f);

				camera->addUIObject("CameraPosition", camPos);
				camera->addUIObject("CameraOrientation", camRot);
				camera->addUIObject("FieldOfView", camFOV);
				camera->addUIObject("EngineName", engName);
				camera->addUIObject("EngineVersion", engVer);
				camera->addUIObject("FrameRate", fpsCount);
			}

			void updateDebugCamera()
			{
				char fpsUI[128];
				snprintf(fpsUI, 128, "FPS %d (%f ms)", Utilities::FrameRate::getFPS(), Utilities::FrameRate::getTimePerFrame());
				fpsCount->setText(fpsUI);
			}
		}
	}
}

