#pragma once

#include "Mesh.h"
#include <vector>

namespace Somnium
{
	namespace Graphics
	{
		class RenderableObject
		{
		/* Methods */
		public:
			RenderableObject() = default;
			RenderableObject(Mesh* mesh, const Maths::Vector3 &position = Maths::Vector3(0,0,0), const Maths::Vector3 &scale = Maths::Vector3(1, 1, 1), const Maths::Vector3 &orientation = Maths::Vector3(0, 0, 0))
				: m_Mesh(mesh), m_Position(position), m_Scale(scale), m_Orientation(orientation){};

			~RenderableObject() {};

			Mesh* getMesh() { return m_Mesh; }
			void  setMesh(Mesh *mesh) { m_Mesh = mesh; }

			void setPosition(float x, float y, float z);
			void setPosition(Maths::Vector3 position) { setPosition(position.x, position.y, position.z); }
			void setScale(float x, float y, float z);
			void setScale(Maths::Vector3 scale) { setScale(scale.x, scale.y, scale.z); }
			void setOrientation(float x, float y, float z);
			void setOrientation(Maths::Vector3 orientation) { setOrientation(orientation.x, orientation.y, orientation.z); }

			inline const Maths::Vector3 getPosition() const { return m_Position; }

			void move(Maths::Vector3 offset);
			void move(Maths::Vector3 direction, float amount);
			void move(Maths::Vector4 movementVector) { move(Maths::Vector3(movementVector.x, movementVector.y, movementVector.z), movementVector.w); }
			void move(float xDir, float yDir, float zDir, float amount) { move(Maths::Vector3(xDir, yDir, zDir), amount); }

			void moveTowards(Maths::Vector3 destination, float amount);
			void moveTowards(Maths::Vector4 movementVector) { moveTowards(Maths::Vector3(movementVector.x, movementVector.y, movementVector.z), movementVector.w); }
			void moveTowards(float x, float y, float z, float amount) { moveTowards(Maths::Vector3(x, y, z), amount); }

			void lookAt(Maths::Vector3 destination);
			void lookAt(float x, float y, float z) { lookAt(Maths::Vector3(x, y, z)); }

			void scale(float x, float y, float z) { scale(Maths::Vector3(x, y, z)); }
			void scale(Maths::Vector3 scaleFactor);

			void rotate(float x, float y, float z) { rotate(Maths::Vector3(x, y, z)); }
			void rotate(Maths::Vector3 rotation);

			void update();

		private:
			Mesh* m_Mesh;
			Maths::Vector3 m_Position;
			Maths::Vector3 m_Scale;
			Maths::Vector3 m_Orientation;
		};
	}
}
