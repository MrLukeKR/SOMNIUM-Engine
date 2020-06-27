#pragma once

#include "Renderer.h"
#include "../Buffers/IndexBuffer.h"
#include "../Buffers/VertexBuffer.h"
#include "../Buffers/VertexArray.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Renderers
		{
			class BatchRenderer : virtual public Renderer
			{
			public:
				BatchRenderer(const Window& window, Cameras::Camera* camera)
					: Renderer(window, camera)
				{
					init();
				};

				~BatchRenderer();

				void beginMapping();
				virtual void submitToQueue(RenderableObject* object);
				virtual void submitToQueue(std::map<char*, RenderableObject*> objects) { for (auto object : objects) submitToQueue(object.second); }
				void endMapping();
				virtual void render(bool flushQueue = false);

			private:
				void init();

			private:
				Buffers::VertexArray*  m_VAO;
				Buffers::VertexBuffer* m_VBO;
				Buffers::IndexBuffer* m_IBO;

				GLfloat* m_VertexDataBuffer;
				unsigned int m_CurrentVertexCount = 0;
				unsigned int m_CurrentIndex;
			};
		}
	}
}
