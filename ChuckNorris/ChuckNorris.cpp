// ChuckNorris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctime> //For Random
#include "ChuckJson.h"
#include "ChuckSocket.h"
#include "BitBoard.h"
#include "MoveGenerator.h"
#include "Play.h"
#include "Evaluation.h"
#include "PlayTree.h"

int main(int argc, char* argv[])
{
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

		GameState* state = ChuckJson::ParseGameState(buffer);
		BitBoard* boardState;

		if(state->whoMoves != 1)
			state->SwapBoard();

		if(state->badMove == true)
			printf("\nDEUMERDA!\n");

		boardState = BitBoard::Generate(state);

		Play* rootPLay = new Play();
		rootPLay->playBitBoard = boardState;

		PlayTree* treeRoot = new PlayTree();
		treeRoot->currentPlay = rootPLay;

		MoveGenerator::GenerateAllMovements(treeRoot);

		int playCounter = 0;
		for(int i = 0; i < treeRoot->possiblePlays->size(); i++)
		{
			PlayTree* myMovement = (*treeRoot->possiblePlays)[i];
			MoveGenerator::GenerateAllMovements(myMovement);

			for(int j = 0; j < myMovement->possiblePlays->size(); j++)
			{
				PlayTree* enemyMovement = (*myMovement->possiblePlays)[j];
				MoveGenerator::GenerateAllMovements(enemyMovement);

				for(int k = 0; k < enemyMovement->possiblePlays->size(); k++)
				{
					PlayTree* mySecondMovement = (*enemyMovement->possiblePlays)[k];
					MoveGenerator::GenerateAllMovements(mySecondMovement);

					playCounter += mySecondMovement->possiblePlays->size();
				}
				playCounter += enemyMovement->possiblePlays->size();
			}
		}
		
		playCounter += treeRoot->possiblePlays->size();

		printf("Jogadas Possiveis: %d\n", playCounter);
		printf("Pecas brancas: %d, Pecas pretas: %d\n", 
			BitBoard::PieceCount(boardState->whitePieces),
			BitBoard::PieceCount(boardState->blackPieces));

		for(int i = 0; i < treeRoot->possiblePlays->size(); i++)
		{
			Evaluation::MiniMax((*treeRoot->possiblePlays)[i], false);
		}
		
		Play* selectedPlay = Play::GetBestChild(treeRoot);

		if(!selectedPlay) //Nothing more todo ;(
			exit(0);

		if(state->whoMoves != 1)
				selectedPlay->SwapPlayCoordinates();

		string playToSend = ChuckJson::GetPlayJson(selectedPlay);
		printf("Jogada: de ");
		selectedPlay->origin.PrintCoordinate();
		printf(" para ");
		selectedPlay->destination.PrintCoordinate();

		p1Socket->Send(playToSend);

		delete treeRoot;
	}
	
	return 0;
}

