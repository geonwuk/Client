#include "QueryClient.h"
#include <iostream>
#include <string>
#include  <fstream>
#include <iomanip>

using namespace std;
//std::ostream& operator<< (std::ostream& os, const Client& c);
TB::Table QueryClient::table{ "id","name","phone number","address" };

QueryClient::QueryClient(ClientManager& cm) : cm{cm}
{
}

void QueryClient::QueryAddClient()
{
	QueryShowClient();
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

	unsigned int id = cm.getMaxIndex();
	table.setFields({ to_string(id),name,phone_number,address });
}

void QueryClient::QueryEraseClient()
{
	QueryShowClient();
	unsigned int id;
	cout << "삭제할 클라이언트 id: ";
	cin >> id;
	bool success = cm.eraseClient(id);
	if (success) {
		cout <<"ID:" << id << " 클라이언트 삭제 완료" << endl;
	}
	else {
		cout <<"ID:"<< id << " 클라이언트는 존재하지 않습니다. 삭제 실패" << endl;
	}
}

void QueryClient::QueryShowClient()
{
	table.print_header();
	auto m = cm.getCleints();
	for (auto& itr : m) {
		const Client& c = itr.second;
		table.print({ std::to_string(c.getId()), c.getName(),c.getPhoneNumber(),c.getAddress()});
	}
	table.print_tail();
}


void QueryClient::QuerySaveClient() {
	std::ofstream out("Clients.txt");
	cm.saveClients(out);
}

void QueryClient::QueryLoadClient()const
{
	std::ifstream in{ "Clients.txt" };
	auto pr = cm.loadClients(in);
	for (auto& i : pr.second) {
		cm.addClient(i.getName(), i.getPhoneNumber(), i.getAddress());
		unsigned int new_id = cm.getMaxIndex();
		table.setFields({ to_string(new_id),i.getName(),i.getPhoneNumber(),i.getAddress() });
	}
}