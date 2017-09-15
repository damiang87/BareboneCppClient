#include <iostream>
#include "../ServerClient/src/ManagerClient.h"

int main(int argc, char* argv[])
{
	Homecode::Software::Client myClient("172.217.20.163", 80); // google server
	if (myClient.Init())
	{
		if (myClient.IsConncted())
		{
			std::cout << "connected...>" << std::endl;
			std::cout << myClient.Request("GET /index.html HTTP/1.1") << std::endl;
		}
	}
	else
	{
		std::cout << "Client invalid!" << std::endl;
	}

	system("PAUSE");
	return 0;
}


