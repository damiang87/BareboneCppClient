#include <iostream>
#include "../ServerClient/src/ManagerClient.h"

int main(int argc, char* argv[])
{
	Ortosoft::Software::Client myClient("192.168.2.105", 123);
	if (myClient.Init())
	{
		if (myClient.IsConncted())
		{
			std::cout << myClient.Request("Admin,123123") << std::endl;
		}
	}
	else
	{
		std::cout << "Client invalid!" << std::endl;
	}

	system("PAUSE");
	return 0;
}

/**
//connection data
std::string ipAddress = "192.168.2.105";
int port = 123;

//socket for connection to remote maschine
WSADATA data;
WORD ver = MAKEWORD(2, 2);
int wsResult = WSAStartup(ver, &data);

if (wsResult != 0)
{
std::cerr << "Can't start winsocket, err: " << wsResult << std::endl;
return 0;
}

SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
if (clientSocket == INVALID_SOCKET)
{
std::cerr << "Can't create socket, err: " << WSAGetLastError() << std::endl;
WSACleanup();
return 0;
}

//structure for connection data
sockaddr_in hint;
hint.sin_family = AF_INET;
hint.sin_port = htons(port);
inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

//connection to the remote machine
int connResult = connect(clientSocket, (sockaddr*)&hint, sizeof(hint));
if (connResult == SOCKET_ERROR)
{
std::cerr << "Can't connect to the server, err: " << WSAGetLastError() << std::endl;
closesocket(clientSocket);
WSACleanup();
return 0;
}

//konv
char buff[4096];
std::string userInput;

do
{
std::getline(std::cin, userInput);

if (userInput.size() > 0)
{
int sendResult = send(clientSocket, userInput.c_str(), userInput.size() + 1, 0);
if (sendResult != SOCKET_ERROR)
{
ZeroMemory(buff, 4096);
int bytesRecv = recv(clientSocket, buff, 4096, 0);
if (bytesRecv > 0)
{
std::cout << "SERVER> " << std::string(buff, 0, bytesRecv) << std::endl;
}
}
}

} while (userInput.size() > 0);

//closesocket(clientSocket);
//WSACleanup();
**/



