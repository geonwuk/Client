#include "ClientManager.h"

unsigned int ClientManager::client_id = 0;
//
//void ClientManager::search_field::test() {
////	Name s { string{"name"}, &Client::getName };
//	//string (Client::*x)()  = &Client::getName;
//}

void ClientManager::addClient(string ID, string name, string phone_number, string address) {
	auto inserted = clients.emplace( client_id, Client{ client_id, ID, name, phone_number, address } );
	clients_by_string.emplace(ID, &inserted.first->second);
	client_id++;
}

bool ClientManager::eraseClient(string ID){
	auto it = clients_by_string.find(ID);
	if (it != clients_by_string.end()) {
		clients.erase(it->second->getId());
		clients_by_string.erase(it);
		return true;
	}
	else {
		return false;
	}
}

const Client& ClientManager::findClient(const string ID) const
{
	auto it = clients_by_string.find(ID);
	return *(it->second);
}

const map<unsigned int, Client>& ClientManager::getCleints() const
{
	return clients;
}

