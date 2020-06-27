#include <iostream>
#include <set>

#ifdef WEB_BUILD
	#include <emscripten.h>
#endif

#define DISABLE_POST_PROCESSING true
#define LIMIT_FRAMERATE false

#include "Audio/AudioEngine.h"

#include "Networking/Centralised/Server.h"

#include "Graphics/Window.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Mesh.h"
#include "Graphics/Renderers/BatchRenderer.h"
#include "Graphics/Renderers/SerialRenderer.h"
#include "Graphics/RenderableObject.h"
#include "Graphics/Cameras/Camera.h"
#include "Graphics/Cameras/FirstPersonCamera.h"
#include "Graphics/Font.h"

#include "Graphics/PostProcessing/PostProcessor.h"
#include "Graphics/PostProcessing/Lighting/Bloom.h"
#include "Graphics/PostProcessing/Filters/Colourise.h"

#include "Logic/Physics/PhysicsEngine.h"

#include "Utilities/FileUtilities.h"
#include "Utilities/FrameRateUtilities.h"
#include "Utilities/DebugTools/ReferenceGrid.h"
#include "Utilities/DebugUtilities.h"

#include "Logic/Game.h"

#include "Examples/AllExamples.h"

using namespace Somnium;
using namespace Audio;
using namespace Graphics;
using namespace Logic;
using namespace Maths;
using namespace Physics;

#ifdef WEB_BUILD
static void startMain(void *mainFunction)
{
	(*(function<void()>*)mainFunction)();
}
#endif

Game* currentGame = NULL;

int main(int argc, char** argv) {
	Utilities::Debug::printWelcomeMessage();
	srand((unsigned)time(0)); 

	std::set<std::string> flags = std::set<std::string>();
	for (int f = 0; f < argc; f++) flags.insert(argv[f]);

	Window myWindow("Somnium Engine", 1920, 1080, (flags.find("-f") != flags.end()) || (flags.find("--fullscreen") != flags.end()));

	Buffers::FrameBuffer::setWindow(&myWindow);

	PostProcessing::PostProcessor::initialise();

	Font* arial = new Font("Resources/Graphics/Fonts/arial.ttf", myWindow.getFreeTypeInstance());
	Shaders::Shader* textShader = new Shaders::Shader("Resources/Graphics/Shaders/Basic/basicText.vs", "Resources/Graphics/Shaders/Basic/basicText.fs");

	#ifdef ENABLE_DEBUG_CAMERA
		Shaders::Shader* naviShader = new Shaders::Shader("Resources/Graphics/Shaders/Debug/navigation.vs", "Resources/Graphics/Shaders/Debug/navigation.fs");
	#endif

	textShader->enable();
	textShader->setMatrix4("projection", Matrix4::orthographic(0, myWindow.getWidth(), 0, myWindow.getHeight(), -1.0f, 100.0f));

	Buffers::FrameBuffer frameBuffer;

	currentGame = new FollowingMonkeys();

	currentGame->init(myWindow);
	Graphics::Cameras::Camera* mainCamera = new Graphics::Cameras::FlyCamera(30, (float)myWindow.getWidth() / myWindow.getHeight(), 0.1f, 1000.0f, false, Vector3(0, 0, 0), Vector3(180, 90, 0));
	currentGame->setActiveCamera(mainCamera);

#ifdef ENABLE_DEBUG_CAMERA
	Utilities::Debug::initialiseDebugCamera(myWindow.getWidth(), myWindow.getHeight(), mainCamera, arial, textShader);
	Utilities::Debug::initialiseReferenceGrid(naviShader, 5, Maths::Vector3(10000));
#endif

	std::vector<RenderableObject*> objects;
	
	Networking::Centralised::Server* myServer = new Networking::Centralised::Server();
	myServer->run();

	Renderers::SerialRenderer* renderer = new Renderers::SerialRenderer(myWindow, mainCamera);
	PhysicsEngine* physics = new PhysicsEngine();


	if (!currentGame)
		throw "No game was loaded";
	else
	{
		currentGame->init(myWindow);
		cout << "Loaded: '" << currentGame->getName() << "'" << endl;
	}

	cout << "---------RUNNING GAME LOOP---------" << endl;

#ifdef WEB_BUILD
	function<void()> webMain = [&]() {
#else

	while (!myWindow.isClosed())
	{
#endif
		Utilities::FrameRate::startFrameCounting();

		myWindow.clear();

		int x, y;

		//1. Process I/O
		myWindow.getMousePosition(x, y);

		//2. Update objects
		Utilities::FrameRate::updateDeltaTime();
		
		currentGame->tick(Utilities::FrameRate::deltaTime);
		renderer->updateCamera(Utilities::FrameRate::deltaTime);
		
		physics->update(Utilities::FrameRate::deltaTime);

		//renderer->beginMapping();

		renderer->submitToQueue(currentGame->getObjects());
		physics->submitToQueue(currentGame->getObjects());


		//3. Draw objects
		//renderer->endMapping();
		frameBuffer.clear();

#if DISABLE_POST_PROCESSING
		renderer->render(true);
#else
		frameBuffer.bind();
		renderer->render(true);
		frameBuffer.unbind();

		//DO POST PROCESSING
		//	1. Submit effects to queue
		static float hue = 0;

		PostProcessing::PostProcessor::submitToQueue(Graphics::PostProcessing::Filters::Colourise::apply(sin(hue), sin(hue + 120), sin(hue + 240), 1));
		hue += 0.01f;

		//	2. Process queue
		PostProcessing::PostProcessor::process(&frameBuffer);
		Graphics::PostProcessing::PostProcessor::drawScreen();
#endif

		Utilities::FrameRate::update();

#ifdef ENABLE_DEBUG_CAMERA
		Utilities::Debug::drawReferenceGrid();
		Utilities::Debug::updateDebugCamera();
#endif

		//4. Post Processing
		mainCamera->updateUI();
		mainCamera->drawUI();
		myWindow.update();

#if LIMIT_FRAMERATE
		Utilities::FrameRate::limitFrameRate(60);
#endif
	};
#ifdef WEB_BUILD
	emscripten_set_main_loop_arg(startMain, &webMain, false, true);
#endif

	cout << "-----------------------------------" << endl;

	return 0;
}
