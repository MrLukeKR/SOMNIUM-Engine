#pragma once

#ifdef WEB_BUILD 
	#define GLFW_INCLUDE_ES3
	#include <GLFW/glfw3.h>
#else 
	#include <glew.h> 
#endif

#include "Shaders/Shader.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexArray.h"
#include <vector>
#include <string>
#include <deque>

namespace Somnium
{
	namespace Graphics
	{
		struct Vertex
		{
			Maths::Vector3 position;
			Maths::Vector3 normal;
			Maths::Vector2 texCoords;
		};

		struct Texture
		{
			GLuint id;
			std::string type;
		};

		class Mesh 
		{
			friend class RenderableObject;

		public:
			Mesh(Buffers::VertexArray* vertexArray, Buffers::IndexBuffer* indexBuffer, std::vector<Texture> textures, Shaders::Shader& shader)
				: m_VAO(vertexArray), m_IBO(indexBuffer), m_Shader(shader), m_Textures(textures) {}

			Mesh(std::vector<GLfloat> vertexArray, std::vector<GLushort> indexBuffer, std::vector<Texture> textures, Shaders::Shader& shader);
			~Mesh() { delete m_VAO; delete m_IBO; };

			const inline Buffers::VertexArray* getVAO() const { return m_VAO; }
			const inline Buffers::IndexBuffer* getIBO() const { return m_IBO; }

			const inline std::vector<Maths::Vector3>& getVertexData() const { return m_VertexData; }
			const inline std::vector<GLushort>& getIndexData() const { return m_IndexData; }

			void setVertexData(std::vector<Maths::Vector3> vertexData);
			void setIndexData(std::vector<GLushort> indexData) { m_IndexData = indexData; }

			inline size_t getIBOSize() const { return m_IBO->getCount(); }
			inline Shaders::Shader& getShader() const { return m_Shader; }
			const Maths::Matrix4 getModelMatrix() const;

		protected:
			void rotate(float xAngle, float yAngle, float zAngle) { rotate(Maths::Vector3(xAngle, yAngle, zAngle)); }
			void rotate(const Maths::Vector3& rotationOffset);

			void scale(float x, float y, float z);
			void scale(const Maths::Vector3& scaleAmount);
			void scale(float uniformScale);

			void translate(float xOffset, float yOffset, float zOffset);
			void translate(const Maths::Vector3& offset);

			void setPosition(const Maths::Vector3& position) { m_Position = position; }
			void setPosition(float x, float y, float z) { m_Position = Maths::Vector3(x, y, z); }

			void setOrientation(const Maths::Vector3& orientation) { m_Orientation = orientation; }
			void setOrientation(float x, float y, float z) { m_Orientation = Maths::Vector3(x, y, z); }

			void setScale(const Maths::Vector3& scale) { m_Scale = scale; }
			void setScale(float x, float y, float z) { m_Scale = Maths::Vector3(x, y, z); }


		protected:
			Buffers::VertexArray* m_VAO;
			Buffers::IndexBuffer* m_IBO;

			std::vector<Maths::Vector3> m_VertexData;
			std::vector<GLushort> m_IndexData;

			Shaders::Shader& m_Shader;

			const std::vector<Texture> m_Textures;

			Maths::Vector3 m_Position = Maths::Vector3(0);
			Maths::Vector3 m_Orientation = Maths::Vector3(0);
			Maths::Vector3 m_Scale = Maths::Vector3(1);
		};
	}
}
