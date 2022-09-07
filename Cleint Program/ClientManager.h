#pragma once
#include <map>
#include <utility>
#include<string>

#include <iosfwd>
#include <vector>
using std::map;
using std::tuple;
using std::pair;
using std::string;

using std::string;
namespace CM {
	class Client {
	public:
		enum class Status { active, resigend, dormant };
		Client(unsigned int id, string name, string phone_number = "NONE", string address = "NONE", Status status = Status::active) :
			id{ id }, name{ name }, phone_number{ phone_number }, address{ address }, status{ status } {}

		string getName() const { return name; }
		string getPhoneNumber() const { return phone_number; }
		string getAddress() const { return address; }
		const unsigned int getId() const { return id; }

	private:

		unsigned int id;
		string name;
		string phone_number;
		string address;
		Status status;

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
		std::pair<std::ifstream&, std::vector<Client>> loadClients(std::ifstream& in);
		const map< unsigned int, Client >& getCleints() const;
		const unsigned int getMaxIndex() const;
	private:
		static unsigned int client_id;
		map< unsigned int, Client > clients;
	};

}




