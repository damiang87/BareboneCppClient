#include <iostream>
#include <string>
#include  <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

#define MAX_BUFFER_SIZE (100 * 1024)

namespace Homecode
{
	namespace Software
	{
		class Client
		{
		public:
			Client(const Client&) = delete;
			Client& operator=(const Client&) = delete;
			Client(std::string ipAddress, int port);
			virtual ~Client();

			bool Init();										//initialize socket and open  connection 
			std::string Request(const std::string request);		//send request to the server and return the answere as string 
			void Deinit();										//close the connection and cleanUp after close [no need to call - done in destructor]
			bool IsConncted() { return m_isConnectedToRemote; } //state of connection

		private:
			void ConnectToRemote();
			bool IsInitialized() { return m_isInitialized; }
			
			SOCKET				m_clientSocket;
			sockaddr_in			m_hint;
			std::string			m_ipAddress;
			int					m_port;
			char				m_buffer[MAX_BUFFER_SIZE];
			bool				m_isInitialized;
			bool				m_isConnectedToRemote;
		};
	}
}