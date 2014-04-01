// ChuckNorris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "json.h"

int _tmain(int argc, _TCHAR* argv[])
{
	string address = "127.0.0.1";

	TCPSocket sock;

	sock.connect("127.0.0.1", 50100);

	Json::Value root;
	root["name"] = "Chuck N0rr1s";

	Json::StyledWriter writer;
	string nameJson = writer.write(root);

	sock.send(nameJson.c_str(), nameJson.length());
	
	char buffer[256];

	while(1)
	{
		sock.recv(buffer, sizeof(buffer));

		printf(buffer);
	}
	

	return 0;
}

