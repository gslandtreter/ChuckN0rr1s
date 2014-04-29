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
