#include "ClientManager.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
using namespace CM;
unsigned int ClientManager::client_id = 0; //클라이언트 ID는 0부터 시작해 고유한 값을 갖는다. (Primary Key)

bool ClientManager::addClient(const string name, const string phone_number, const string address) {
	//이름, 핸드폰 번호, 주소 값을 받아 클라이언트를 생성하고 성공하면 true, 실패하면 false를 리턴
	bool success;
	tie(ignore, success) = clients.emplace( client_id, move(Client{ client_id, name, phone_number, address }) );
	client_id++;
	return success;
}

bool ClientManager::eraseClient(const unsigned int id){
	//id에 해당하는 클라이언트 정보를 삭제
	using int_type = decltype(clients)::size_type;
	int_type success = clients.erase(id);
	if (success == 1)
		return true;
	else
		return false;
}

const Client& ClientManager::findClient(const unsigned int id) const{
	//id에 해당하는 클라이언트를 찾고 만약 맵에 존재하면 해당 클라이언트를 리턴하고 없으면 no_client 객체를 리턴
	auto it = clients.find(id);
	if (it == clients.end()) {
		return no_client;//헤더파일에 선언이 되어 있음
	}
	else {
		return it->second;//id에 해당하는 클라이언트.
	}
}

std::ofstream& operator<<(std::ofstream& out, const Client& c){
	//클라이언트 정보를 저장할 떄 CSV포맷에 맞게 저장
	out << c.getId() << ',' << c.getName() << ',' << c.getPhoneNumber() << ',' << c.getAddress();
	return out;
}

const map<unsigned int, Client>& ClientManager::getCleints() const{
	//모든 클라이언트를 조회하고 싶을 때 clients를 받아서 조회
	return clients;
}


ofstream& ClientManager::saveClients(ofstream& out) const{
	//지금까지 맵에 저장된 클라이언트를 순회하며 저장
	for (const auto& c : clients) {
		out << c.second << endl;
	}
	return out;
}

std::pair<std::ifstream&, std::vector<Client>> ClientManager::loadClients(std::ifstream& in) const {
	vector<Client> client_vector;
	std::string str;
	while (std::getline(in, str)) {
		//한줄씩 실행
		vector<string> tmp;//, 사이에 있는 값들을 저장할 컨테이너
		auto beg = str.find_first_not_of(',');
		while (beg != string::npos) { //CSV 파일 포맷 파싱 중
			//한줄에 있는 , 수 만큼 반복합니다
			auto endIdx = str.find_first_of(',', beg);
			if (endIdx == string::npos) {
				endIdx = str.length();
			}
			tmp.emplace_back(str.substr(beg, endIdx - beg));
			beg = str.find_first_not_of(',', endIdx);
		}
		//CSV 파일 포맷    id,   이름,전화번호,주소
		//            tmp[0],tmp[1],tmp[2],tmp[3]
		string address = tmp[3];
		string phone_number = tmp[2];
		string name = tmp[1];
		unsigned int id = stoul(tmp[0]);
		client_vector.emplace_back(id, name, phone_number, address);
	}
	return {in, move(client_vector)}; //콘솔화면에 출력할 때 얼마나 테이블 크기를 늘려야 하는지 알기 위해서 client_vector를 리턴합니다.
}

const unsigned int ClientManager::getMaxIndex() const{
	//맵으로 저장되어 있으므로 end()전이 가장 큰 id값을 가지고 있습니다.
	return (--clients.end())->first;
}

bool CM::operator==(const Client& c, const NoClient&){
	//findCleint 함수를 호출하고 받은 리턴값이 no_client인지 확인할 때 쓰는 함수입니다.
	//Client c = findClient(id);
	//if(c==no_client)
	const Client& nc { no_client };
	if (&c == &nc)
		return true;
	else
		return false;
}
