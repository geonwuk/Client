#include "ClientManager.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
using namespace CM;
unsigned int ClientManager::client_id = 0; //Ŭ���̾�Ʈ ID�� 0���� ������ ������ ���� ���´�. (Primary Key)

bool ClientManager::addClient(const string name, const string phone_number, const string address) {
	//�̸�, �ڵ��� ��ȣ, �ּ� ���� �޾� Ŭ���̾�Ʈ�� �����ϰ� �����ϸ� true, �����ϸ� false�� ����
	bool success;
	tie(ignore, success) = clients.emplace( client_id, move(Client{ client_id, name, phone_number, address }) );
	client_id++;
	return success;
}

bool ClientManager::eraseClient(const unsigned int id){
	//id�� �ش��ϴ� Ŭ���̾�Ʈ ������ ����
	using int_type = decltype(clients)::size_type;
	int_type success = clients.erase(id);
	if (success == 1)
		return true;
	else
		return false;
}

const Client& ClientManager::findClient(const unsigned int id) const{
	//id�� �ش��ϴ� Ŭ���̾�Ʈ�� ã�� ���� �ʿ� �����ϸ� �ش� Ŭ���̾�Ʈ�� �����ϰ� ������ no_client ��ü�� ����
	auto it = clients.find(id);
	if (it == clients.end()) {
		return no_client;//������Ͽ� ������ �Ǿ� ����
	}
	else {
		return it->second;//id�� �ش��ϴ� Ŭ���̾�Ʈ.
	}
}

std::ofstream& operator<<(std::ofstream& out, const Client& c){
	//Ŭ���̾�Ʈ ������ ������ �� CSV���˿� �°� ����
	out << c.getId() << ',' << c.getName() << ',' << c.getPhoneNumber() << ',' << c.getAddress();
	return out;
}

const map<unsigned int, Client>& ClientManager::getCleints() const{
	//��� Ŭ���̾�Ʈ�� ��ȸ�ϰ� ���� �� clients�� �޾Ƽ� ��ȸ
	return clients;
}


ofstream& ClientManager::saveClients(ofstream& out) const{
	//���ݱ��� �ʿ� ����� Ŭ���̾�Ʈ�� ��ȸ�ϸ� ����
	for (const auto& c : clients) {
		out << c.second << endl;
	}
	return out;
}

std::pair<std::ifstream&, std::vector<Client>> ClientManager::loadClients(std::ifstream& in) const {
	vector<Client> client_vector;
	std::string str;
	while (std::getline(in, str)) {
		//���پ� ����
		vector<string> tmp;//, ���̿� �ִ� ������ ������ �����̳�
		auto beg = str.find_first_not_of(',');
		while (beg != string::npos) { //CSV ���� ���� �Ľ� ��
			//���ٿ� �ִ� , �� ��ŭ �ݺ��մϴ�
			auto endIdx = str.find_first_of(',', beg);
			if (endIdx == string::npos) {
				endIdx = str.length();
			}
			tmp.emplace_back(str.substr(beg, endIdx - beg));
			beg = str.find_first_not_of(',', endIdx);
		}
		//CSV ���� ����    id,   �̸�,��ȭ��ȣ,�ּ�
		//            tmp[0],tmp[1],tmp[2],tmp[3]
		string address = tmp[3];
		string phone_number = tmp[2];
		string name = tmp[1];
		unsigned int id = stoul(tmp[0]);
		client_vector.emplace_back(id, name, phone_number, address);
	}
	return {in, move(client_vector)}; //�ܼ�ȭ�鿡 ����� �� �󸶳� ���̺� ũ�⸦ �÷��� �ϴ��� �˱� ���ؼ� client_vector�� �����մϴ�.
}

const unsigned int ClientManager::getMaxIndex() const{
	//������ ����Ǿ� �����Ƿ� end()���� ���� ū id���� ������ �ֽ��ϴ�.
	return (--clients.end())->first;
}

bool CM::operator==(const Client& c, const NoClient&){
	//findCleint �Լ��� ȣ���ϰ� ���� ���ϰ��� no_client���� Ȯ���� �� ���� �Լ��Դϴ�.
	//Client c = findClient(id);
	//if(c==no_client)
	const Client& nc { no_client };
	if (&c == &nc)
		return true;
	else
		return false;
}
