#pragma once

#include "../Graphics/Cameras/Camera.h"
#include "../Graphics/RenderableObject.h"
#include "../Graphics/Shaders/Shader.h"
#include "../Logic/Physics/PhysicsEngine.h"

namespace Somnium 
{
	class Game
	{

	public:
		virtual void init(Graphics::Window& myWindow) {};
		virtual void tick(float deltaTime) {};

		const std::map<char*, Graphics::RenderableObject*>& getObjects() const { return m_Objects; }
		const std::string& getName() const { return m_GameName; }

		Graphics::Cameras::Camera* const getActiveCamera() const { return m_MainCamera; }
		void setActiveCamera(Graphics::Cameras::Camera* camera) { m_MainCamera = camera; }
		void setActiveCamera(Graphics::Cameras::Camera& camera) { m_MainCamera = &camera; }
	
	protected:
		Game(std::string gameName) : m_GameName{gameName} {};
		Game(const Game& gameToCopy) {};
		Game(Game&& gameToMove) {};
		virtual ~Game() 
		{
			delete m_MainCamera;
			for (auto obj : m_Objects) delete obj.second;
			for (auto mesh = m_Meshes.begin(); mesh != m_Meshes.end(); mesh ++) delete mesh->second;
			for (auto shader = m_Shaders.begin(); shader != m_Shaders.end(); shader++) delete shader->second;

			m_Objects.clear();
			m_Meshes.clear();
			m_Shaders.clear();
		};
		
	protected:
		std::string m_GameName;
		Graphics::Cameras::Camera* m_MainCamera = NULL;
		Logic::Physics::PhysicsEngine* m_PhysicsEngine = NULL;
		
		std::map<char*, Graphics::Cameras::Camera*> m_Cameras;
		std::map<char*, Graphics::Font*> m_Fonts;
		std::map<char*, Graphics::RenderableObject*> m_Objects;
		std::map<char*, Graphics::Mesh*> m_Meshes;
		std::map<char*, Graphics::Shaders::Shader*> m_Shaders;
	};
}