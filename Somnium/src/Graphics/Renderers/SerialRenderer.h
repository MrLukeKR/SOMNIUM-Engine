#pragma once
#include <vector>
#include <queue>
#include "../RenderableObject.h"
#include "../Cameras/Camera.h"
#include "../Window.h"
#include "Renderer.h"
#include "../Buffers/FrameBuffer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Renderers
		{
			class SerialRenderer
				: virtual public Renderer
			{
				/* Methods */
			public:
				SerialRenderer(const Window& window, Cameras::Camera* camera)
					: Renderer(window, camera) {};
				virtual void submitToQueue(RenderableObject* object) { m_RenderQueue.push(object); }
				virtual void submitToQueue(std::map<char*, RenderableObject*> objects) { for (auto object : objects) m_RenderQueue.push(object.second); }
				virtual void render(bool flushQueue = false);

			private:
				std::queue<RenderableObject*> m_RenderQueue;
			};
		}
	}
}
