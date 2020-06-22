#include <iostream>
#include <set>

#include "../Graphics/Window.h"

#include "../Graphics/Mesh.h"

#include "../Graphics/Font.h"

#include "../Graphics/PostProcessing/PostProcessor.h"
#include "../Graphics/PostProcessing/Lighting/Bloom.h"
#include "../Graphics/PostProcessing/Filters/Colourise.h"

#include "../Utilities/FileUtilities.h"
#include "../Utilities/DebugTools/ReferenceGrid.h"

#include "../Logic/Game.h"

using namespace Somnium;
using namespace Graphics;
using namespace Maths;

class PhysicsMonkeys : public Game
{
public:
	PhysicsMonkeys() : Game("Physics Monkeys") {}

	/*
	This example will spawn a set of monkeys in set positions and apply a physics simulation to each of them
	*/

	void init(Window& myWindow) {
		m_PhysicsEngine = new Logic::Physics::PhysicsEngine();
		
		m_MainCamera = new Camera(30, (float)myWindow.getWidth() / myWindow.getHeight(), 0.1f, 1000.0f, false, Vector3(0, 0, 0), Vector3(180, 90, 0));

		Font* arial = new Font("Resources/Graphics/Fonts/arial.ttf", myWindow.getFreeTypeInstance());

		m_Shaders.insert({ "PBR/basic", new Shaders::Shader("Resources/Graphics/Shaders/PBR/basic.vs", "Resources/Graphics/Shaders/PBR/basic.fs") });
		m_Shaders.insert({ "Basic/basicText", new Shaders::Shader("Resources/Graphics/Shaders/Basic/basicText.vs", "Resources/Graphics/Shaders/Basic/basicText.fs") });

#ifdef ENABLE_DEBUG_CAMERA
		Shaders::Shader* naviShader = new Shaders::Shader("Resources/Graphics/Shaders/Debug/navigation.vs", "Resources/Graphics/Shaders/Debug/navigation.fs");
#endif

		Graphics::Shaders::Shader* textShader = m_Shaders.at("Basic/basicText");
		textShader->enable();
		textShader->setMatrix4("projection", Matrix4::orthographic(0, myWindow.getWidth(), 0, myWindow.getHeight(), -1.0f, 100.0f));

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

		char buff[24];
		for (unsigned int i = 0; i < 5; i++)
		{
			sprintf_s(buff, "lightColors[%d]", i);
			shader->setVector3(buff, Maths::Vector3(3000.0f, 3000.0f, 3000.0f));
		}

		Buffers::FrameBuffer frameBuffer;

		Matrix4 view = Matrix4::identity();

		m_Meshes.insert({ "monkey", new Mesh(Utilities::File::loadOBJ("Resources/Graphics/Objects/Monkey.obj", *shader)) });

		m_Objects.insert({ "monkey", new RenderableObject(new Mesh(*m_Meshes.at("monkey"))) });

		m_Objects.at("monkey")->setScale(1, 1, 1);
		m_Objects.at("monkey")->setPosition(-10, 5, -10);
		m_Objects.at("monkey")->rotate(0, 45, 0);
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