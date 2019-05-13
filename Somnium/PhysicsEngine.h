#pragma once

#include <string>

namespace Physics
{
	class PhysicsEngine
	{
	public:
		PhysicsEngine();
		~PhysicsEngine();

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