// ChuckNorris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChuckJason.h"
#include "ChuckSocket.h"

int _tmain(int argc, _TCHAR* argv[])
{

	ChuckSocket* p1Socket = new ChuckSocket("127.0.0.1", 50100);
	ChuckSocket* p2Socket = new ChuckSocket("127.0.0.1", 50200);
	
	p1Socket->Connect();
	p2Socket->Connect();

	if(!p1Socket->IsConnected() || !p2Socket->IsConnected())
	{
		printf("Erro ao conectar!");
		exit(0);
	}

	string nameJson = ChuckJason::GetNameJson("Chuck N0rr15");
	p1Socket->Send(nameJson);

	nameJson = ChuckJason::GetNameJson("Bozo");
	p2Socket->Send(nameJson);

	char buffer[1024];
	while(1)
	{
		int bytesReceived = p1Socket->Receive(buffer, sizeof(buffer));

		buffer[bytesReceived] = '\0';

		printf("%s\n\n", buffer);
	}
	

	return 0;
}

