#pragma once
#include <map>
#include <utility>
#include<string>
#include "Client.h"
#include <iosfwd>
#include <vector>
using std::map;
using std::tuple;
using std::pair;
using std::string;

class ClientManager
{
public:
	bool addClient(const string name, const string phone_number = "NONE", const string address = "NONE");
	bool eraseClient(const unsigned int id);
	const Client& findClient(const unsigned int id) const;
	std::ofstream& saveClients(std::ofstream& out) const;
	std::pair<std::ifstream&, std::vector<Client>> loadClients(std::ifstream& in);
	const map< unsigned int, Client >& getCleints() const;
	const unsigned int getMaxIndex() const;
private:
	static unsigned int client_id;
	map< unsigned int, Client > clients;
};

