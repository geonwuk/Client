#include "ClientManager.h"
#include <iostream>
#include <string>
#include <fstream>
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

std::ofstream& operator<<(std::ofstream& out, const Client& c)
{
	out << c.getId() << ',' << c.getName() << ',' << c.getPhoneNumber() << ',' << c.getAddress();
	return out;
}

const map<unsigned int, Client>& ClientManager::getCleints() const
{
	return clients;
}


ofstream& ClientManager::saveClients(ofstream& out) const
{
	for (const auto& c : clients) {
		out << c.second << endl;
	}
	return out;
}

std::pair<std::ifstream&, std::vector<Client>> ClientManager::loadClients(std::ifstream& in) {
	vector<Client> client_vector;
	std::string str;
	while (std::getline(in, str)) {
		vector<string> tmp;
		auto beg = str.find_first_not_of(',');
		while (beg != string::npos) {
			auto endIdx = str.find_first_of(',', beg);
			if (endIdx == string::npos) {
				endIdx = str.length();
			}
			tmp.emplace_back(str.substr(beg, endIdx - beg));
			beg = str.find_first_not_of(',', endIdx);
		}
		string address = tmp[3];
		string phone_number = tmp[2];
		string name = tmp[1];
		unsigned int id = stoul(tmp[0]);
		client_vector.emplace_back(id, name, phone_number, address);
	}

	return {in, move(client_vector)};
}

const unsigned int ClientManager::getMaxIndex() const
{
	return (--clients.end())->first;
}
