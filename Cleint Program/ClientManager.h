#pragma once
#include <map>
#include <utility>
#include <string>
#include <iosfwd>
#include <vector>


namespace CM {
	using std::map;
	using std::string;
	class Client {
	public:
		Client(unsigned int id, string name, string phone_number = "NONE", string address = "NONE") :
			id{ id }, name{ name }, phone_number{ phone_number }, address{ address } {}
		const unsigned int getId() const { return id; }
		string getName() const { return name; }
		string getPhoneNumber() const { return phone_number; }
		string getAddress() const { return address; }
	private:
		unsigned int id;
		string name;
		string phone_number;
		string address;
	protected:
		Client() = default;
	};

	struct NoClient : public Client { };
	const NoClient no_client{};
	bool operator== (const Client& c, const NoClient&);

	class ClientManager
	{
	public:
		bool addClient(const string name, const string phone_number = "NONE", const string address = "NONE");
		bool eraseClient(const unsigned int id);
		const Client& findClient(const unsigned int id) const;
		std::ofstream& saveClients(std::ofstream& out) const;
		std::pair<std::ifstream&, std::vector<Client>> loadClients(std::ifstream& in) const ;
		const map< unsigned int, Client >& getCleints() const;
		const unsigned int getMaxIndex() const;
	private:
		static unsigned int client_id;
		map< unsigned int, Client > clients;
	};

}




