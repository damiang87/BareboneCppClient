#include "ManagerClient.h"

Homecode::Software::Client::Client(std::string ipAddress, int port)
	:m_ipAddress(ipAddress), m_port(port)
{
	m_isConnectedToRemote = false;
	m_isInitialized = false;
}

Homecode::Software::Client::~Client()
{
	Deinit();
}

bool Homecode::Software::Client::Init()
{
	//socket for connection to remote maschine 
	if (!m_isInitialized)
	{
		WSADATA data;
		WORD ver = MAKEWORD(2, 2);
		int wsResult = WSAStartup(ver, &data);

		if (wsResult != 0)
		{
			std::cerr << "Can't start winsocket, err: " << wsResult << std::endl;
			return false;
		}

		SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (clientSocket == INVALID_SOCKET)
		{
			std::cerr << "Can't create socket, err: " << WSAGetLastError() << std::endl;
			WSACleanup();
			return false;
		}

		m_clientSocket = clientSocket;
		m_isInitialized = true;
		ConnectToRemote();
		return true;
	}
	else
	{
		return false;
	}
}

std::string Homecode::Software::Client::Request(const std::string request)
{
	if (IsConncted())
	{
		int sendResult = send(m_clientSocket, request.c_str(), request.size() + 1, 0);
		if (sendResult != SOCKET_ERROR)
		{
			ZeroMemory(m_buffer, MAX_BUFFER_SIZE);
			int bytesRecv = recv(m_clientSocket, m_buffer, MAX_BUFFER_SIZE, 0);
			if (bytesRecv > 0)
			{
				return std::string(m_buffer, 0, bytesRecv);
			}
		}
		else
		{
			m_isConnectedToRemote = false;
			return std::string("0");
		}
	}
	else
		return std::string("0");
}

void Homecode::Software::Client::Deinit()
{
	if (IsConncted())
	{
		closesocket(m_clientSocket);
		m_isConnectedToRemote = false;
	}
	if (IsInitialized())
	{
		m_isInitialized = false;
		WSACleanup();
	}
	return;
}

void Homecode::Software::Client::ConnectToRemote()
{
	if (!IsConncted())
	{
		m_hint.sin_family = AF_INET;
		m_hint.sin_port = htons(m_port);
		inet_pton(AF_INET, m_ipAddress.c_str(), &m_hint.sin_addr);

		//make connection
		int connResult = connect(m_clientSocket, (sockaddr*)&m_hint, sizeof(m_hint));
		if (connResult == SOCKET_ERROR)
		{
			m_isConnectedToRemote = false;
			std::cerr << "Can't connect to the server, err: " << WSAGetLastError() << std::endl;
			closesocket(m_clientSocket);
			WSACleanup();
			return;
		}
		else
		{
			m_isConnectedToRemote = true;
		}
	}
	else
		return;
}
