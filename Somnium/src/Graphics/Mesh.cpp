#include "Mesh.h"
#include "../Logic/Maths/Quaternion.h"

namespace Somnium
{
	namespace Graphics
	{
		void Mesh::scale(float uniformScale)
		{
			scale(Maths::Vector3(uniformScale));
		}

		void Mesh::scale(float x, float y, float z)
		{
			scale(Maths::Vector3(x, y, z));
		}

		void Mesh::scale(const Maths::Vector3& scaleAmount)
		{
			m_Scale *= scaleAmount;
		}

		void Mesh::translate(float x, float y, float z)
		{
			translate(Maths::Vector3(x, y, z));
		}

		void Mesh::translate(const Maths::Vector3& translation)
		{
			m_Position += translation;
		}

		void Mesh::rotate(const Maths::Vector3& rotation)
		{
			m_Orientation *= Maths::Quaternion::fromEulerAngles(rotation);
		}

		void Mesh::setVertexData(std::vector<Maths::Vector3> vertexData) 
		{ 
			m_VertexData = vertexData; 
		}



		const Maths::Matrix4 Mesh::getModelMatrix() const
		{	
			Maths::Matrix4 modelMatrix = Maths::Matrix4::identity();

			modelMatrix *= Maths::Matrix4::scale(m_Scale) *
				m_Orientation.toTransformationMatrix() *
				Maths::Matrix4::translation(m_Position);

			return modelMatrix;
		}
	}
}
