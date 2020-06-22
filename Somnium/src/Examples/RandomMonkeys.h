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

class RandomMonkeys : public Game
{
public:
	RandomMonkeys() : Game("Random Monkeys") {}

	void init(Window& myWindow) {
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

		const char objectName[24] = "monkey";
		
		for (unsigned int i = 0; i < 50; i++)
		{
			char* objectID = new char[10]; // Allow 24 char item names + 10 chars of ID (allows 4294967295 instantiations of each object)
			char* objectRef = new char[34];

			sprintf_s(objectID, sizeof(char[10]), "%d", i);
			strcpy_s(objectRef, sizeof(char[24]), objectName);
			strcat_s(objectRef, sizeof(char[10]), objectID);

			m_Objects.insert({ objectRef, new RenderableObject(new Mesh(*m_Meshes.at("monkey"))) });
		}

		for (auto iterObj : m_Objects)
		{
			RenderableObject* object = iterObj.second;

			float scale = (float)rand() / RAND_MAX;
			object->setScale(scale, scale, scale);
			object->setPosition((float)rand() / RAND_MAX * 10 * ((rand() % 2) ? 1 : -1), (float)rand() / RAND_MAX * 10 * ((rand() % 2) ? 1 : -1), (float)rand() / RAND_MAX * -50.0f);
		}
	}

	void tick(float deltaTime)
	{
		//1. Get logic input	
		//2. Update objects
		static float offset = 0.1f * deltaTime;


		//renderer->beginMapping();

		for (auto iterObj : m_Objects)
		{
			RenderableObject* object = iterObj.second;

			float xRot = (float)rand() / RAND_MAX * ((rand() % 2) ? 1 : -1) * offset;
			float yRot = (float)rand() / RAND_MAX * ((rand() % 2) ? 1 : -1) * offset;
			float zRot = (float)rand() / RAND_MAX * ((rand() % 2) ? 1 : -1) * offset;

			object->move((rand() % 2) ? 1 : -1 , (rand() % 2) ? 1 : -1, (rand() % 2) ? 1 : -1, offset / 10);
			object->rotate(xRot, yRot, zRot); //TODO: Setup a glPop/glPushMatrix() functionality system
		}

		Graphics::Shaders::Shader * shader = m_Shaders.at("PBR/basic");
		shader->enable();
		shader->setVector3("lightPositions[4]", m_MainCamera->getPosition());

		//3. Draw objects


		//4. Post Processing
	}
};