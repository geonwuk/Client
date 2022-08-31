#include "ClientManager.h"
unsigned int ClientManager::client_id = 0;

void ClientManager::search_field::test() {
	Name s { string{"name"}, &Client::getName };
	//string (Client::*x)()  = &Client::getName;
}

void ClientManager::addClient(string name, string phone_number, string address) {
	clients.emplace( client_id++, Client{ name, phone_number, address } );
}

bool ClientManager::eraseClient(string ID){
	auto cmp = [](const Client*& i, const Client*& j) -> bool { return false; };
	map < string, Client*, decltype(cmp)> cache(cmp);
	for (auto i : clients) {
		
	}
	//clients.find()
	return false;
}

