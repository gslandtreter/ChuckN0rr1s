// ChuckNorris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctime> //For Random
#include "ChuckJson.h"
#include "ChuckSocket.h"
#include "BitBoard.h"
#include "MoveGenerator.h"
#include "Play.h"

int _tmain(int argc, _TCHAR* argv[])
{

	/*
	bitBoard_t teste = 17592186044416 >> 6;

	BitBoard::PrintBitBoard(teste);
	BitBoard::PrintBitBoard(BitBoard::GoWest(teste));
	BitBoard::GetPieceCoordinate(teste).PrintCoordinate();
	*/

	ChuckSocket* p1Socket = new ChuckSocket("127.0.0.1", 50200);
	//ChuckSocket* p2Socket = new ChuckSocket("127.0.0.1", 50200);
	
	p1Socket->Connect();
	//p2Socket->Connect();

	if(!p1Socket->IsConnected()/* || !p2Socket->IsConnected()*/)
	{
		printf("Erro ao conectar!");
		exit(0);
	}

	string nameJson = ChuckJson::GetNameJson("Chuck N0rr15");
	p1Socket->Send(nameJson);

	//nameJson = ChuckJson::GetNameJson("Bozo");
	//p2Socket->Send(nameJson);

	char buffer[1024];
	while(1)
	{
		srand(time(0));

		int bytesReceived = p1Socket->Receive(buffer, sizeof(buffer));

		bool sentMove = false;

		GameState* state = ChuckJson::ParseGameState(buffer);
		state->Print();

		if(state->whoMoves != 1)
			continue;

		if(state->badMove == true)
		{
			printf("\nDEUMERDA!\n");
		}

		BitBoard* boardState = BitBoard::Generate(state);

		BitBoard::PrintBitBoard(boardState->fullBoard);

		vector<Play*>* newStates = MoveGenerator::GenerateAllMovements(boardState);

		printf("Jogadas Possiveis: %d\n", newStates->size());

		if(!newStates->size())
			exit(0);

		int randomPlay = rand() % newStates->size();

		Play* selectedPlay = (*newStates)[randomPlay];

		string playToSend = ChuckJson::GetPlayJson(selectedPlay);
		printf("Mandei de ");
		selectedPlay->origin.PrintCoordinate();
		printf(" para ");
		selectedPlay->destination.PrintCoordinate();

		p1Socket->Send(playToSend);
		sentMove = true;
	}
	
	return 0;
}

