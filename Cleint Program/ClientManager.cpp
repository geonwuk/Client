#include "ClientManager.h"
//#include <utility>
using namespace std;
unsigned int ClientManager::client_id = 0;

bool ClientManager::addClient(const string name, const string phone_number, const string address) {
	bool success;
	tie(ignore, success) = clients.emplace( client_id, Client{ client_id, name, phone_number, address } );
	client_id++;
	return success;
}

bool ClientManager::eraseClient(const unsigned int id){
	using int_type = decltype(clients)::size_type;
	int_type success = clients.erase(id);

	if (success == 1)
		return true;
	else
		return false;
}

const Client& ClientManager::findClient(const unsigned int id) const
{
	//todo: emptyCLient;
	auto it = clients.find(id);
	return it->second;
}

const map<unsigned int, Client>& ClientManager::getCleints() const
{
	return clients;
}