// ChuckNorris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChuckJson.h"
#include "ChuckSocket.h"
#include "BitBoard.h"
#include "MoveGenerator.h"
#include "Play.h"

int _tmain(int argc, _TCHAR* argv[])
{

	/*bitBoard_t teste = 17592186044416 >> 5;

	BitBoard::PrintBitBoard(teste);
	BitBoard::GetPieceCoordinate(teste).PrintCoordinate();*/


	ChuckSocket* p1Socket = new ChuckSocket("127.0.0.1", 50100);
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
		int bytesReceived = p1Socket->Receive(buffer, sizeof(buffer));

		bool sentMove = false;

		GameState* state = ChuckJson::ParseGameState(buffer);
		state->Print();

		if(state->whoMoves != 1)
			continue;

		BitBoard* boardState = BitBoard::Generate(state);

		BitBoard::PrintBitBoard(boardState->whitePieces);

		vector<bitBoard_t>* gotWhitePawns = MoveGenerator::GetWhitePawns(boardState);

		for(int i = 0; i < gotWhitePawns->size(); i++)
		{
			vector<Play*>* newStates = MoveGenerator::GeneratePawnMovements(boardState, (*gotWhitePawns)[i]);

			for(int n = 0; n < newStates->size(); n++)
			{
				Play* selectedPlay = (*newStates)[n];

				string playToSend = ChuckJson::GetPlayJson(selectedPlay);

				p1Socket->Send(playToSend);
				sentMove = true;
				break;
			}

			if(sentMove)
				break;
		}
	}
	

	return 0;
}

