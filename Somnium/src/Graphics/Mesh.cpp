#include "Mesh.h"
#include "../Logic/Maths/Quaternion.h"

namespace Somnium
{
	namespace Graphics
	{
		Mesh::Mesh(Buffers::VertexArray* vertexArray, Buffers::IndexBuffer* indexBuffer, std::vector<Texture> textures, Shaders::Shader& shader)
			: m_VAO(vertexArray), m_IBO(indexBuffer), m_Shader(shader), m_Textures(textures)
		{
			
		}

		void Mesh::scale(float uniformScale)
		{
			scale(Maths::Vector3(uniformScale));
		}

		void Mesh::scale(float x, float y, float z)
		{
			scale(Maths::Vector3(x, y, z));
		}

		void Mesh::scale(Maths::Vector3 scaleAmount)
		{
			m_Scale *= scaleAmount;
		}

		void Mesh::translate(float x, float y, float z)
		{
			translate(Maths::Vector3(x, y, z));
		}

		void Mesh::translate(Maths::Vector3 translation)
		{
			m_Position += translation;
		}

		void Mesh::rotate(Maths::Vector3 rotation)
		{
			m_Orientation += rotation;
		}

		const Maths::Matrix4 Mesh::getModelMatrix() const
		{	
			Maths::Matrix4 modelMatrix = Maths::Matrix4::identity();
			Maths::Quaternion rotation = Maths::Quaternion(m_Orientation);

			modelMatrix *= Maths::Matrix4::scale(m_Scale) *
				Maths::Matrix4::rotationZ(m_Orientation.z) *
				Maths::Matrix4::rotationY(m_Orientation.y) *
				Maths::Matrix4::rotationZ(m_Orientation.x) *
				Maths::Matrix4::translation(m_Position);

			return modelMatrix;
		}
	}
}
