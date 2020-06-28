#pragma once

#define MAX_VERTICES 100000
#define RENDERER_VERTEX_SIZE 8
#define RENDERER_BUFFER_SIZE MAX_VERTICES * RENDERER_VERTEX_SIZE
#define INDEX_AMOUNT MAX_VERTICES * 3

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
				std::vector<Maths::Matrix4> m_Transformations;

				GLuint m_VAO;
				GLuint m_VBO;
				Buffers::IndexBuffer* m_IBO;

				Vertex* m_VertexDataBuffer;
				unsigned int m_CurrentVertexCount = 0;
				unsigned int m_CurrentIndex;
				bool m_Mapped = false;
			};
		}
	}
}
