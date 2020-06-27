#pragma once

#ifdef WEB_BUILD 
	#define GLFW_INCLUDE_ES3
	#include <GLFW/glfw3.h>
#else 
	#include <glew.h> 
#endif

#include "../Logic/Maths/Maths.h"
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
			Mesh(Buffers::VertexArray* vertexArray, Buffers::IndexBuffer* indexBuffer, std::vector<Texture> textures, Shaders::Shader& shader);
			Mesh(std::vector<GLfloat> vertexArray, std::vector<GLushort> indexBuffer, std::vector<Texture> textures, Shaders::Shader& shader);
			~Mesh() { delete m_VAO; delete m_IBO; };

			const inline Buffers::VertexArray* getVAO() const { return m_VAO; }
			const inline Buffers::IndexBuffer* getIBO() const { return m_IBO; }

			const inline std::vector<GLfloat>& getVertexData() const { return m_VertexData; }
			const inline std::vector<GLushort>& getIndexData() const { return m_IndexData; }

			inline size_t getIBOSize() const { return m_IBO->getCount(); }
			inline Shaders::Shader& getShader() const { return m_Shader; }
			const Maths::Matrix4 getModelMatrix() const;

		protected:
			void rotate(float xAngle, float yAngle, float zAngle) { rotate(Maths::Vector3(xAngle, yAngle, zAngle)); }
			void rotate(Maths::Vector3 rotationOffset);

			void scale(float x, float y, float z);
			void scale(Maths::Vector3 scaleAmount);
			void scale(float uniformScale);

			void translate(float xOffset, float yOffset, float zOffset);
			void translate(Maths::Vector3 offset);

		protected:
			Buffers::VertexArray* m_VAO;
			Buffers::IndexBuffer* m_IBO;

			std::vector<GLfloat> m_VertexData;
			std::vector<GLushort> m_IndexData;

			Shaders::Shader& m_Shader;

			const std::vector<Texture> m_Textures;

			Maths::Matrix4 m_ModelMatrix = Maths::Matrix4::identity();
		};
	}
}
