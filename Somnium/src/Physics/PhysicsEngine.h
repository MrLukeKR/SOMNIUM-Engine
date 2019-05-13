#pragma once

#include <string>
#include <iostream>

namespace Physics
{
	class PhysicsEngine
	{
	public:
		PhysicsEngine();
		~PhysicsEngine();

		static void initialise()
		{
			std::cout << "--------[INITIALISING PHYSICS]--------" << std::endl;

			std::cout << " SOMNIUM Physics Engine " << PhysicsEngine::getVersion() << std::endl;

			std::cout << "--------------------------------------" << std::endl;
		}

		static std::string getVersion()
		{
			std::string version = "V"
				+ std::to_string(PhysicsEngine::VERSION_MAJOR)
				+ std::string(".")
				+ std::to_string(PhysicsEngine::VERSION_MINOR);

			return version;
		}

	private:
		static const int VERSION_MAJOR = 0, VERSION_MINOR = 1;
	};
}