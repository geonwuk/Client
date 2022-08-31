#pragma once
#include <map>
#include <tuple>
#include "Client.h"

using std::map;
using std::tuple;
using std::pair;
class ClientManager
{

public:
	void addClient(string name, string phone_number = "NONE", string address = "NONE");
	bool eraseClient(string ID);


private:
	static unsigned int client_id;
	map< unsigned int, Client > clients;
	
	static class search_field {
		using Name = pair<string, string (Client::*)() const>;
		using Phone_number = pair<string, string (Client::*)() const>;
		using Adress = pair<string, string Client::*>;
		using Status = pair<string, Client::Status >;

		search_field() = delete;
		const tuple<Name, Phone_number> fields { { "name", & Client::getName }, {"phone_number", &Client::getPhoneNumber}};

		void test();
		
	};

};

