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
		//Used for random seed.
		srand(time(0));

		int bytesReceived = p1Socket->Receive(buffer, sizeof(buffer));

		GameState* state = ChuckJson::ParseGameState(buffer);
		BitBoard* boardState = BitBoard::Generate(state);

		BitBoard::PrintBitBoard(boardState->fullBoard);

		if(state->whoMoves != 1)
			state->SwapBoard();

		if(state->badMove == true)
			printf("\nDEUMERDA!\n");

		boardState = BitBoard::Generate(state);
		//vector<Play*>* newStates = MoveGenerator::GenerateAllMovements(boardState);

		Play* rootPLay = new Play();
		rootPLay->playBitBoard = boardState;

		PlayTree* treeRoot = new PlayTree();
		treeRoot->currentPlay = rootPLay;

		MoveGenerator::GenerateAllMovements(treeRoot);

		int playCounter = 0;
		int lastLevel = 0;
		for(int i = 0; i < treeRoot->possiblePlays->size(); i++)
		{
			PlayTree* myMovement = (*treeRoot->possiblePlays)[i];
			MoveGenerator::GenerateAllMovements(myMovement);

			for(int j = 0; j < myMovement->possiblePlays->size(); j++)
			{
				PlayTree* enemyMovement = (*myMovement->possiblePlays)[j];
				MoveGenerator::GenerateAllMovements(enemyMovement);

				playCounter += enemyMovement->possiblePlays->size();
			}

			playCounter += treeRoot->possiblePlays->size();
		}
			/*vector<Play*>* enemyMovements = MoveGenerator::GenerateAllMovements(BitBoard::Swap((*newStates)[i]->playBitBoard));
			//printf("Jogada %d, numero de movimentos do inimigo: %d\n", i+1, enemyMovements->size());

			playCounter++;
			for(int n = 0; n < enemyMovements->size(); n++)
			{
				vector<Play*>* mySecondLevel = MoveGenerator::GenerateAllMovements(BitBoard::Swap((*enemyMovements)[n]->playBitBoard));
				//printf("Jogada %d-%d, numero de movimentos do inimigo: %d\n", i+1, n+1, mySecondLevel->size());

				playCounter++;

				for(int m = 0; m < mySecondLevel->size(); m++)
				{
					vector<Play*>* enemySecondLevel = MoveGenerator::GenerateAllMovements(BitBoard::Swap((*mySecondLevel)[m]->playBitBoard));
					//printf("Jogada %d-%d-%d, numero de movimentos do inimigo: %d\n", i+1, n+1, m+1, enemySecondLevel->size());

					playCounter++;

					for(int k = 0; k < enemySecondLevel->size(); k++)
					{
						vector<Play*>* myThirdLevel = MoveGenerator::GenerateAllMovements(BitBoard::Swap((*enemySecondLevel)[k]->playBitBoard));
						//printf("Jogada %d-%d-%d-%d, numero de movimentos do inimigo: %d\n", i+1, n+1, m+1, k+1, myThirdLevel->size());

						playCounter++;
						lastLevel++;
					}
				}
			}

			playCounter++;
		}*/

		printf("Jogadas Possiveis: %d, Ultimo nivel: %d\n", playCounter, lastLevel);
		printf("Pecas brancas: %d, Pecas pretas: %d\n", 
			BitBoard::PieceCount(boardState->whitePieces),
			BitBoard::PieceCount(boardState->blackPieces));

		for(int i = 0; i < treeRoot->possiblePlays->size(); i++)
		{
			Evaluation::MiniMax((*treeRoot->possiblePlays)[i], false);
		}
		
		Play* selectedPlay = Play::GetBestChild(treeRoot);

		if(state->whoMoves != 1)
				selectedPlay->SwapPlayCoordinates();

		string playToSend = ChuckJson::GetPlayJson(selectedPlay);
		printf("Jogada: de ");
		selectedPlay->origin.PrintCoordinate();
		printf(" para ");
		selectedPlay->destination.PrintCoordinate();

		p1Socket->Send(playToSend);

		//delete treeRoot;
	}
	
	return 0;
}

