#include "QueryClient.h"
#include <iostream>
#include <string>
#include  <fstream>
#include <iomanip>

using namespace std;
using namespace CM;

TB::Table QueryClient::table{ "id","name","phone number","address" }; //고객조회시 출력할 테이블 필드들을 입력한다

QueryClient::QueryClient(ClientManager& cm) : cm{cm} {}

void QueryClient::QueryAddClient(){
	QueryShowClient();
	string name;
	string phone_number;
	string address;
	cout << "name: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, name);
	cout << "phone number: ";
	getline(cin, phone_number);
	cout << "address: ";
	getline(cin, address);
	cm.addClient(name, phone_number, address);

	unsigned int id = cm.getMaxIndex();
	table.setFields({ to_string(id),name,phone_number,address });
	//추가할 Client의 각 필드별(id, name, phone_number, address)의 최대길이를 알기 위해 setFields를 호출한다
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

void QueryClient::QueryShowClient(){
	table.printHeader();
	auto m = cm.getCleints();		      //map::iterator
	for (auto itr : m) {
		const Client& c = itr.second;     //iterator로부터 client 객체를 받는다
		table.print({ std::to_string(c.getId()), c.getName(),c.getPhoneNumber(),c.getAddress()}); //테이블형식으로 출력
	}
	table.printTail();
}


void QueryClient::QuerySaveClient() {
	std::ofstream out("Clients.txt");
	cm.saveClients(out);				//ClientManager가 저장을 담당한다										
}

void QueryClient::QueryLoadClient(){										//파일 불러오기 메소드
	std::ifstream in{ "Clients.txt" };										//clients.txt를 연다
	auto pr = cm.loadClients(in);											//clientManager에서 파일에 저장된 Client들을 벡터로 리턴한 것을 받는다.
	for (auto& i : pr.second) {												
		cm.addClient(i.getName(), i.getPhoneNumber(), i.getAddress());		//파일에서 Client 불러온 정보를 추가한다.
		unsigned int new_id = cm.getMaxIndex();												  
		table.setFields({ to_string(new_id),i.getName(),i.getPhoneNumber(),i.getAddress() }); //id, name, phone_number, address
		//추가한 항목들에 대해 최대 문자열 길이를 각 필드별로 파악해서 table 객체에 저장한다
	}
}