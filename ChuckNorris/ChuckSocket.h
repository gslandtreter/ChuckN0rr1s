#pragma once

#include <string>
#include <stdio.h>
#include "PracticalSocket.h"

using namespace std;

class ChuckSocket
{

private:
	string address;
	int port;
	bool isConnected;
	
	TCPSocket socket;

public:
	ChuckSocket(string address, int port);
	~ChuckSocket(void);

	bool Connect();
	bool Disconnect();

	bool IsConnected();

	void Send(string text);
	int Receive(void *buffer, int bufferLength);
};

