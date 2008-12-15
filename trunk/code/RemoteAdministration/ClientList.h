#pragma once
//#include "ClientEventHandler.h"
#include <vector>

class ClientEventHandler;

/**
 * Implement a list with all the connected clients.
 * 
 * Collaboration:
 * - GUI
 * - ClientEventHandler
 */
class ClientList	
{

public:

	ClientList();
	~ClientList();
	static ClientList* Instance();
	void Push(ClientEventHandler* ceh);
	void Pop();
	ClientEventHandler* Front();
	ClientEventHandler* Back();
	ClientEventHandler* At(int i);
	void Erease(ClientEventHandler *ceh);
	int Size();

private:
	std::vector <ClientEventHandler *> clientList;
	static ClientList *instance;

};