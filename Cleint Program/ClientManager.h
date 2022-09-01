#pragma once
#include <map>
#include <tuple>
#include<string>
#include "Client.h"

using std::map;
using std::tuple;
using std::pair;
using std::string;

class ClientManager
{
public:
	//(unsigned int id, string ID, string name, string phone_number = "NONE", string address = "NONE", Status status = Status::active)
	void addClient(string ID, string name, string phone_number = "NONE", string address = "NONE");
	bool eraseClient(string ID);
	void test() {}

	const map< unsigned int, Client >& getCleints() const;

private:
	static unsigned int client_id;
	map< unsigned int, Client > clients;
	
	static class search_field {
		//using Name = pair<string, string (Client::*)() const>;
	//	using Phone_number = pair<string, string (Client::*)() const>;
	//	using Adress = pair<string, string Client::*>;
		//using Status = pair<string, Client::Status >;

		search_field() = delete;
	//	const tuple<Name, Phone_number> fields { { "name", & Client::getName }, {"phone_number", &Client::getPhoneNumber}};

		void test();
		
	};
	
	std::map < string, Client* > clients_by_string;

};

