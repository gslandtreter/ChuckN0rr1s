// ChuckNorris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChuckJson.h"
#include "ChuckSocket.h"
#include "BitBoard.h"

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

	string nameJson = ChuckJson::GetNameJson("Chuck N0rr15");
	p1Socket->Send(nameJson);

	nameJson = ChuckJson::GetNameJson("Bozo");
	p2Socket->Send(nameJson);

	char buffer[1024];
	while(1)
	{
		int bytesReceived = p1Socket->Receive(buffer, sizeof(buffer));

		GameState* state = ChuckJson::ParseGameState(buffer);
		state->Print();

		BitBoard* boardState = BitBoard::Generate(state);
	}
	

	return 0;
}

