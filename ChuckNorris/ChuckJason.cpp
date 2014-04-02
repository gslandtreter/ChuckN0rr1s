#include "ChuckJason.h"


ChuckJason::ChuckJason(void)
{
}


ChuckJason::~ChuckJason(void)
{
}

string ChuckJason::GetNameJson( string name )
{
	Json::Value root;
	root["name"] = name;

	Json::StyledWriter writer;
	string nameJson = writer.write(root);

	return nameJson;
}
