#pragma once

#include "../Graphics/Camera.h"
#include "../Graphics/RenderableObject.h"
#include "../Graphics/Shaders/Shader.h"

namespace Somnium 
{
	class Game
	{

	public:
		virtual void init(Graphics::Window& myWindow) {};
		virtual void tick(int mouseX, int mouseY) {};
		
		
		std::vector<Graphics::RenderableObject*> getObjects() { return m_Objects; }
		const std::string& getName() const { return m_GameName; }

	protected:
		Game(std::string gameName) {};
		Game(const Game& gameToCopy) {};
		Game(Game&& gameToMove) {};
		virtual ~Game() 
		{
			delete m_MainCamera;
			for (auto obj : m_Objects) delete obj;
			for (auto mesh = m_Meshes.begin(); mesh != m_Meshes.end(); mesh ++) delete mesh->second;
			for (auto shader = m_Shaders.begin(); shader != m_Shaders.end(); shader++) delete shader->second;

			m_Objects.clear();
			m_Meshes.clear();
			m_Shaders.clear();
		};
		
	protected:
		std::string m_GameName;
		Graphics::Camera* m_MainCamera = NULL;
		std::vector<Graphics::RenderableObject*> m_Objects;
		std::map<char*, Graphics::Mesh*> m_Meshes;
		std::map<char*, Graphics::Shaders::Shader*> m_Shaders;
	};
}