#pragma once

#include "../NetworkEntity.h"
#include <string>

#define CLIENT_PORT 20080

namespace Somnium
{
	namespace Networking
	{
		namespace Centralised
		{
			class Client
			: public NetworkEntity
			{
			public:
				Client() { }
				virtual ~Client();

#ifdef _WIN32
				bool connectToServer();
#else
				bool connectToServer(struct sockaddr_in serverAddress);
#endif

				void broadcastMessage(std::string message) {};
				void sendMessage(std::string address, std::string message) {};
				void processMessage(std::string message) {};
				void disconnect() {};

			private:
				//Server m_ServerAddr;
			};
		}
	}
}
