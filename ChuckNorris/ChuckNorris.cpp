// ChuckNorris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctime> //For Random
#include "ChuckJson.h"
#include "ChuckSocket.h"
#include "BitBoard.h"
#include "MoveGenerator.h"
#include "Play.h"

int main(int argc, char* argv[])
{

	

	/*bitBoard_t teste = 17592186044416 << 14;

	BitBoard::PrintBitBoard(teste);
	BitBoard::PrintBitBoard(BitBoard::GoNorthEast(teste));
	BitBoard::GetPieceCoordinate(teste).PrintCoordinate();
	*/

	char *address = "127.0.0.1";
	int port = 50200;

	if(argc == 3)
	{
		address = argv[1];
		port = atoi(argv[2]);
	}

	printf("Conectando a %s:%d\n", address, port);
	ChuckSocket* p1Socket = new ChuckSocket(address, port);
	
	p1Socket->Connect();

	if(!p1Socket->IsConnected())
	{
		printf("Erro ao conectar!");
		exit(0);
	}

	printf("Conectado!\n");
	string nameJson = ChuckJson::GetNameJson("Chuck N0rr15");
	p1Socket->Send(nameJson);

	char buffer[1024];
	while(1)
	{
		srand(time(0));

		int bytesReceived = p1Socket->Receive(buffer, sizeof(buffer));

		bool sentMove = false;

		GameState* state = ChuckJson::ParseGameState(buffer);
		
		state->PrintBoard();

		if(state->whoMoves != 1)
		{
			state->SwapBoard();
		}

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

		if(state->whoMoves != 1)
		{
			selectedPlay->SwapPlayCoordinates();
		}

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

