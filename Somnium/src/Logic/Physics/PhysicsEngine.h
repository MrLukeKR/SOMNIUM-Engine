#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "PhysicsObject.h"
#include "../Maths/Vector3.h"
#include "../../Graphics/RenderableObject.h"

namespace Somnium
{
	namespace Logic
	{
		namespace Physics
		{
			class PhysicsEngine
			{
			public:
				PhysicsEngine();
				~PhysicsEngine();

				void update(float deltaTime)
				{

				}

				void submitToQueue(PhysicsObject* object)
				{

				}

				void submitToQueue(std::vector<PhysicsObject*> objects)
				{

				}

				void submitToQueue(std::map<char*, Graphics::RenderableObject*> objects)
				{
					//for (auto object : objects)
						//submitToQueue(object->getPhysicsObjects());
				}

				static std::string getVersion()
				{
					std::string version = "V"
						+ std::to_string(PhysicsEngine::VERSION_MAJOR)
						+ std::string(".")
						+ std::to_string(PhysicsEngine::VERSION_MINOR);

					return version;
				}

			protected:
				Maths::Vector3 gravity = Maths::Vector3(0, -9.8f, 0);

			private:
				static const int VERSION_MAJOR = 0, VERSION_MINOR = 1;
			};
		}
	}
};