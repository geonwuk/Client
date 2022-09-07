#pragma once
#include <map>
#include <utility>
#include <string>
#include <iosfwd>
#include <vector>

namespace CM {
	using std::map;
	using std::string;
	class Client {//������
	public:
		Client(unsigned int id, string name, string phone_number = "NONE", string address = "NONE") :
			id{ id }, name{ name }, phone_number{ phone_number }, address{ address } {}
		const unsigned int getId() const { return id; }          //��id getter
		string getName() const { return name; }                  //���̸�getter
		string getPhoneNumber() const { return phone_number; }   //����ȭ��ȣgetter
		string getAddress() const { return address; }            //���ּ�getter
	private:
		unsigned int id;        //�����ͺ��̽� PK�� �� id
		string name;            //���̸�
		string phone_number;    //����ȭ��ȣ
		string address;         //���ּ�
	protected:
		Client() :id{}, name{}, phone_number{}, address{}{};
	};

	struct NoClient : public Client { };                  //findClient(id)���� ���� id�� �ش��ϴ� ���� ���ٸ� ������ Ŭ����
	const NoClient no_client{};                           //NoClient ��ü
	bool operator== (const Client& c, const NoClient&);   //findClient(id)���� ���� ��ü�� no_client�� ���Ͽ� ����� �� �ְ� ������ �����ε�

	class ClientManager{//ClientŬ������ �����ϴ� Ŭ����
	public:
		bool addClient(const string name, const string phone_number = "NONE", const string address = "NONE");  //���߰�
		bool eraseClient(const unsigned int id);															   //������
		const Client& findClient(const unsigned int id) const; //�ֹ������� ���Ϸκ��� �ε��� �� �� �ֹ��� �ִ� �� id�� �ִ��� Ȯ���ϱ� ���ؼ� �� �Լ��� �ֹ����� Ŭ�������� ȣ���Ѵ�.
		std::ofstream& saveClients(std::ofstream& out) const;								                   //������ ���Ϸ� ���� (CSV����)
		std::pair<std::ifstream&, std::vector<Client>> loadClients(std::ifstream& in) const ;                  //������ ���Ͽ��� �ҷ����� (CSV����)
		const map< unsigned int, Client >& getCleints() const;                                                 //
		const unsigned int getMaxIndex() const;
	private:
		static unsigned int client_id;
		map< unsigned int, Client > clients;
	};

}




