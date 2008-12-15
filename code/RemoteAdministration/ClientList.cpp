#include "ClientList.h"

ClientList *ClientList::instance = 0;

ClientList::ClientList(){

}

ClientList::~ClientList(){

}

ClientList* ClientList::Instance(){

	if(instance == 0)
		instance = new ClientList();

	return instance;
}

void ClientList::Push(ClientEventHandler* ceh){
	clientList.push_back(ceh);
};

void ClientList::Pop(){
	clientList.pop_back();
};

ClientEventHandler* ClientList::Front(){
	return clientList.front();
};

ClientEventHandler* ClientList::Back(){
	return clientList.back();
};

ClientEventHandler* ClientList::At(int i){
	return clientList.at(i);
};

void ClientList::Erease(ClientEventHandler *ceh){
	std::vector<ClientEventHandler *>::iterator walker= clientList.begin();
	for(unsigned int i = 0; i < clientList.size(); i++)
		if(ceh == clientList.at(i)){
			clientList.erase(walker);
			break;
		}
		walker++;
};

int ClientList::Size(){
	return clientList.size();
}