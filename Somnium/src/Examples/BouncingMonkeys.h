#include <iostream>
#include <set>

#include "../Graphics/Window.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Cameras/FlyCamera.h"
#include "../Graphics/PostProcessing/PostProcessor.h"
#include "../Graphics/PostProcessing/Lighting/Bloom.h"
#include "../Graphics/PostProcessing/Filters/Colourise.h"

#include "../Utilities/FileUtilities.h"
#include "../Utilities/DebugTools/ReferenceGrid.h"

#include "../Logic/Game.h"

using namespace Somnium;
using namespace Graphics;
using namespace Maths;

class BouncingMonkeys : public Game
{
public:
	BouncingMonkeys() : Game("Bouncing Monkeys") {}

	/*
	This example will spawn a set of monkeys in set positions and apply a physics simulation to each of them
	*/

	void init(Window& myWindow) {
		m_PhysicsEngine = new Logic::Physics::PhysicsEngine();
		
		m_Cameras.insert({ "Main", new Cameras::FlyCamera(45, (float)myWindow.getWidth() / myWindow.getHeight(), 0.1f, 1000.0f, false, Vector3(0, 10, 0), Vector3(200, 90, 0)) });
		m_MainCamera = m_Cameras.at("Main");

		m_Shaders.insert({ "PBR/basic", new Shaders::Shader("Resources/Graphics/Shaders/PBR/basic.vs", "Resources/Graphics/Shaders/PBR/basic.fs") });

			Graphics::Shaders::Shader* shader = m_Shaders.at("PBR/basic");
		shader->enable();
		shader->setVector3("albedo", Maths::Vector3(1, 1, 1));
		shader->setFloat("ao", 0.01);
		shader->setFloat("metallic", 0.9f);
		shader->setFloat("roughness", 0.1f);

		shader->setVector3("lightPositions[0]", Maths::Vector3(-10.0f, 10.0f, 10.0f));
		shader->setVector3("lightPositions[1]", Maths::Vector3(10.0f, 10.0f, 10.0f));
		shader->setVector3("lightPositions[2]", Maths::Vector3(-10.0f, -10.0f, 10.0f));
		shader->setVector3("lightPositions[3]", Maths::Vector3(10.0f, -10.0f, 10.0f));

		static const int buffSize = 24;
		char buff[buffSize];

		for (unsigned int i = 0; i < 5; i++)
		{
#ifdef _WIN32
			sprintf_s(buff, buffSize, "lightColors[%d]", i);
#else
			snprintf(buff, buffSize, "lightColors[%d]", i);
#endif
	
			shader->setVector3(buff, Maths::Vector3(3000.0f, 3000.0f, 3000.0f));
		}

		Buffers::FrameBuffer frameBuffer;

		Matrix4 view = Matrix4::identity();

		m_Meshes.insert({ "monkey", new Mesh(Utilities::File::loadOBJ("Resources/Graphics/Objects/Monkey.obj", *shader)) });

		m_Objects.insert({ "monkey", new RenderableObject(new Mesh(*m_Meshes.at("monkey"))) });

		m_Objects.at("monkey")->setScale(1, 1, 1);
		m_Objects.at("monkey")->setPosition(0, 10, 30);
		m_Objects.at("monkey")->setOrientation(0, 180, 0);
	}

	void tick(int mouseX, int mouseY)
	{
		//1. Get logic input	
		//2. Update objects

		//renderer->beginMapping();

		Graphics::Shaders::Shader * shader = m_Shaders.at("PBR/basic");
		shader->enable();
		shader->setVector3("lightPositions[4]", m_MainCamera->getPosition());

		//3. Draw objects

		//4. Post Processing
	}
};