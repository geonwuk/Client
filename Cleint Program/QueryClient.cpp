#include "QueryClient.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "Table.h"
using namespace std;
std::ostream& operator<< (std::ostream& os, const Client& c);

std::array<unsigned int, 4> QueryClient::fields{};

QueryClient::QueryClient(ClientManager& cm) : cm{cm}
{
	fields[0] = string{ "id" }.size();
	fields[1] = string{ "name" }.size();
	fields[2] = string{ "phone number" }.size();
	fields[3] = string{ "address" }.size();
	TB::Table<3> s{ "1","2","3" };

}

void QueryClient::QueryAddClient()
{
	string name;
	string phone_number;
	string address;
	cout << "name: ";
	cin >> name;
	fields[1] = name.size();
	cout << "phone number: ";
	cin >> phone_number;
	fields[2] = phone_number.size();
	cout << "address: ";
	cin >> address;
	fields[3] = address.size();
	cm.addClient(name, phone_number, address);
	auto c = cm.getCleints();
	unsigned int id = (--c.end())->first;
	fields[0] = string{ "id" }.size() > std::to_string(id).size() ? string{ "id" }.size(): std::to_string(id).size();
	for (auto f : fields) {
		cout << f << " ";
	}
}

void QueryClient::QueryEraseClient()
{
	unsigned int id;
	cout << "id: ";
	cin >> id;
	bool success = cm.eraseClient(id);
}
void QueryClient::print(CONTENT content, char start, char pad) {
	unsigned int idx = 0;
	for (auto f : fields) {
		cout << start;
		cout<<pad<<setw(f)<<setfill(pad)<<content[idx++]<<pad;
	}
	cout << start<<endl;
	
}

void QueryClient::QueryShowClient()
{
	print({ "","","","" }, '+', '-');
	print({ "id","name","phone number","address" }, '|', ' ');
	print({ "","","","" }, '+', '-');
	auto m = cm.getCleints();
	for (auto& itr : m) {
		const Client& c = itr.second;
		print({ std::to_string(c.getId()), c.getName(),c.getPhoneNumber(),c.getAddress()},'|',' ');
	}
	print({ "","","","" }, '+', '-');
	
}
//Client(unsigned int id, string ID, string name, string phone_number = "NONE", string address = "NONE", Status status = Status::active) :
std::ostream& operator<< (std::ostream& os, const Client& c) {
	cout << "id: " << c.getId() << " ";
	cout << "Name: " << c.getName()<<" ";
	cout << "Phone: " << c.getPhoneNumber()<<" ";
	cout << "Address: " << c.getAddress()<<" ";
	return os;
}