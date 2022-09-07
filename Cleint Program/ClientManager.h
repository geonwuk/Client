#pragma once
#include <map>
#include <utility>
#include <string>
#include <iosfwd>
#include <vector>

namespace CM {
	using std::map;
	using std::string;
	class Client {//고객정보
	public:
		Client(unsigned int id, string name, string phone_number = "NONE", string address = "NONE") :
			id{ id }, name{ name }, phone_number{ phone_number }, address{ address } {}
		const unsigned int getId() const { return id; }          //고객id getter
		string getName() const { return name; }                  //고객이름getter
		string getPhoneNumber() const { return phone_number; }   //고객전화번호getter
		string getAddress() const { return address; }            //고객주소getter
	private:
		unsigned int id;        //데이터베이스 PK로 쓸 id
		string name;            //고객이름
		string phone_number;    //고객전화번호
		string address;         //고객주소
	protected:
		Client() :id{}, name{}, phone_number{}, address{}{};
	};

	struct NoClient : public Client { };                  //findClient(id)에서 만약 id에 해당하는 고객이 없다면 리턴할 클래스
	const NoClient no_client{};                           //NoClient 객체
	bool operator== (const Client& c, const NoClient&);   //findClient(id)에서 받은 객체를 no_client와 비교하여 사용할 수 있게 연산자 오버로딩

	class ClientManager{//Client클래스를 관리하는 클래스
	public:
		bool addClient(const string name, const string phone_number = "NONE", const string address = "NONE");  //고객추가
		bool eraseClient(const unsigned int id);															   //고객삭제
		const Client& findClient(const unsigned int id) const; //주문정보를 파일로부터 로드할 때 그 주문에 있는 고객 id가 있는지 확인하기 위해서 이 함수를 주문정보 클래스에서 호출한다.
		std::ofstream& saveClients(std::ofstream& out) const;								                   //고객정보 파일로 저장 (CSV포맷)
		std::pair<std::ifstream&, std::vector<Client>> loadClients(std::ifstream& in) const ;                  //고객정보 파일에서 불러오기 (CSV포맷)
		const map< unsigned int, Client >& getCleints() const;                                                 //
		const unsigned int getMaxIndex() const;
	private:
		static unsigned int client_id;
		map< unsigned int, Client > clients;
	};

}




