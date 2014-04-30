#include "ChuckJson.h"


ChuckJson::ChuckJson(void)
{
}


ChuckJson::~ChuckJson(void)
{
}

string ChuckJson::GetNameJson( string name )
{
	Json::Value root;
	root["name"] = name;

	Json::StyledWriter writer;
	string nameJson = writer.write(root);

	return nameJson;
}

GameState* ChuckJson::ParseGameState( string gameStateJson )
{
	Json::Value root;
	Json::Reader reader;

	reader.parse(gameStateJson, root);

	GameState* newGameState = new GameState();

	newGameState->board = root.get("board",NULL).asString();
	newGameState->enpassant = Coordinate::Parse(root.get("enpassant",NULL).asString());
	newGameState->whoMoves = root.get("who_moves",0).asInt();
	newGameState->badMove = root.get("bad_move",false).asBool();
	newGameState->whiteInfractions = root.get("white_infractions",0).asInt();
	newGameState->blackInfractions = root.get("black_infractions",0).asInt();
	newGameState->winner = root.get("winner",0).asInt();
	newGameState->fiftyMoves = root.get("50moves",false).asBool();
	newGameState->draw = root.get("draw",false).asBool();

	return newGameState;
}

std::string ChuckJson::GetPlayJson( Play* play )
{
	if(!play)
		return NULL;

	char sourceCoord[64];
	char destCoord[16];

	
	sprintf(sourceCoord, "{\"to\": [%d, %d], \"from\": [%d, %d]}", play->destination.x, play->destination.y ,play->origin.x, play->origin.y);
	//sprintf(sourceCoord, "[%d, %d]", play->origin.x, play->origin.y);
	//sprintf(destCoord, "[%d, %d]", play->destination.x, play->destination.y);

	return sourceCoord;
	Json::Value root;
	root["to"] = destCoord;
	root["from"] = sourceCoord;

	Json::StyledWriter writer;
	string playJson = writer.write(root);

	return playJson;
}
