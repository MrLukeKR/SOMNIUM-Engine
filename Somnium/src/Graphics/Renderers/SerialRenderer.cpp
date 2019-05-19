#include "SerialRenderer.h"
#include "../../Logic/Maths/Maths.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Renderers
		{
			void SerialRenderer::render(bool flushQueue)
			{
				std::queue<RenderableObject*> tempQueue;
				if(!flushQueue)	tempQueue = m_RenderQueue;

				while (!m_RenderQueue.empty()) {
					RenderableObject* object = m_RenderQueue.front();
					m_RenderQueue.pop();

					const Mesh* mesh = object->getMesh();

					mesh->getShader().enable();

					mesh->getShader().setMatrix4("projectionMatrix", m_Camera.getProjection());
					mesh->getShader().setMatrix4("viewMatrix", m_Camera.getView());
					mesh->getShader().setMatrix4("modelMatrix", mesh->getModelMatrix());
					mesh->getShader().setVector3("camPos", m_Camera.getPosition());

					mesh->getVAO()->bind();
					mesh->getIBO()->bind();

					mesh->getVAO()->draw(mesh->getIBO()->getCount());

					mesh->getIBO()->unbind();
					mesh->getVAO()->unbind();
				}

				if(!flushQueue)	m_RenderQueue = tempQueue;
			}
		}
	}
}
