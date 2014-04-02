#include "ChuckSocket.h"


ChuckSocket::ChuckSocket( string address, int port )
{
	this->address = address;
	this->port = port;

	this->isConnected = false;
}


ChuckSocket::~ChuckSocket(void)
{
}

bool ChuckSocket::Connect()
{
	if(isConnected)
		return true;

	try
	{
		socket.connect(this->address, this->port);
		this->isConnected = true;
		return true;
	}
	catch (SocketException e)
	{
		printf(e.what());
		return false;
	}
}

bool ChuckSocket::Disconnect()
{

	return true;
}

void ChuckSocket::Send( string text )
{
	if(!isConnected)
		return;

	try
	{
		socket.send(text.c_str(), text.length());
	}
	catch (SocketException e)
	{
		printf(e.what());
	}
}

int ChuckSocket::Receive( void *buffer, int bufferLenght )
{
	if(!isConnected)
		return -1;

	try
	{
		int bytesRead = socket.recv(buffer, bufferLenght);
		return bytesRead;
	}
	catch (SocketException e)
	{
		printf(e.what());
		return -1;
	}
	return 0;
}

bool ChuckSocket::IsConnected()
{
	return this->isConnected;
}
