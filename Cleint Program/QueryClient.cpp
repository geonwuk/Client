#include "QueryClient.h"
#include <iostream>
#include <string>
#include<functional>
using std::cout;
using std::cin;
using std::string;
using std::endl;
std::ostream& operator<< (std::ostream& os, const Client& c);

const unsigned int QueryClient::padding = 1;
unsigned int QueryClient::id_f = 0;
unsigned int QueryClient::name_f = 0;
unsigned int QueryClient::phone_f = 0;
unsigned int QueryClient::address_f = 0;


void QueryClient::QueryAddClient()
{
	string name;
	string phone_number;
	string address;
	cout << "name: ";
	cin >> name;
	cout << "phone number: ";
	cin >> phone_number;
	cout << "address: ";
	cin >> address;
	cm.addClient(name, phone_number, address);
}

void QueryClient::QueryEraseClient()
{
	unsigned int id;
	cout << "id: ";
	cin >> id;
	cm.eraseClient(id);
}

void QueryClient::QueryShowClient()
{
	//auto m = cm.getCleints();
	//for (auto& i : m) {
	//	cout << i.second << endl;;
	//}
	//cout << endl;
}
//Client(unsigned int id, string ID, string name, string phone_number = "NONE", string address = "NONE", Status status = Status::active) :
std::ostream& operator<< (std::ostream& os, const Client& c) {
	cout << "id: " << c.getId() << " ";
	cout << "Name: " << c.getName()<<" ";
	cout << "Phone: " << c.getPhoneNumber()<<" ";
	cout << "Address: " << c.getAddress()<<" ";
	return os;
}