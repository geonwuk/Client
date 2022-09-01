#include "QueryClient.h"
#include <iostream>
#include <string>
#include<functional>
using std::cout;
using std::cin;
using std::string;
using std::endl;
void QueryClient::QueryAddClient()
{
	string ID;
	string name;
	string phone_number;
	string address;
	cout << "ID: ";
	cin >> ID;
	cout << "name: ";
	cin >> name;
	cout << "phone number: ";
	cin >> phone_number;
	cout << "address: ";
	cin >> address;
	cm.addClient(ID, name, phone_number, address);
}

void QueryClient::QueryEraseClient()
{
	string ID;
	cout << "ID: ";
	cin >> ID;
	cm.eraseClient(ID);
}

void QueryClient::QueryTest()
{
	string test;
	cout << "test echo: ";
	cin >> test;
	cout << test;
}

void QueryClient::QueryShowClient()
{
	auto m = cm.getCleints();
	for (auto& i : m) {
		cout << std::cref(i.second) << endl;;
	}
	cout << endl;
}
//Client(unsigned int id, string ID, string name, string phone_number = "NONE", string address = "NONE", Status status = Status::active) :
std::ostream& operator<< (std::ostream& os, const Client c) {
	cout << "Name: " << c.getName()<<" ";
	cout << "Phone: " << c.getPhoneNumber()<<" ";
	cout << "Address: " << c.getAddress()<<" ";
	return os;
}