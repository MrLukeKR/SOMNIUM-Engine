#pragma once

#ifdef _WIN32

#else
	#include <sys/socket.h>
	#include <netinet/in.h>
#endif

#include <string>
#include <cerrno>
#include <iostream>

namespace Somnium
{
	namespace Networking
	{
	enum NetworkError { CREATE_SOCKET_FAIL, BIND_SOCKET_FAIL, SERVER_LISTEN_FAIL };

		class NetworkEntity
		{
		public:
			virtual ~NetworkEntity(){};

			virtual void broadcastMessage(std::string message) = 0;
			virtual void sendMessage(std::string address, std::string message) = 0;
			virtual void processMessage(std::string message) = 0;


		protected:
			NetworkEntity() {};
			int m_SocketID = 0;

		protected:
			void printError(NetworkError errorCode)
						{
							switch(errorCode)
							{
							case NetworkError::CREATE_SOCKET_FAIL:
								std::cerr << "Socket creation failed on SERVER: ";
								break;
							case NetworkError::BIND_SOCKET_FAIL:
								std::cerr << "Socket binding failed on SERVER: ";
								break;
							case NetworkError::SERVER_LISTEN_FAIL:
								std::cerr << "Failed to set the socket mode to listen on SERVER: ";
								break;
							default:
								std::cerr << "Error on SERVER: ";
								break;
							}

							char errorMessage[1024];
#ifdef _WIN32
							strerror_s(errorMessage, errno);
#else
							strerror(errno);
#endif

							std::cerr << errorMessage << std::endl;
						}
		};
	}
}
