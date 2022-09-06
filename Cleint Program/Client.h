#pragma once
#include <string>
#include <iosfwd>

using std::string;

class Client{
public:
	enum class Status { active, resigend, dormant };
	Client(unsigned int id, string name, string phone_number = "NONE", string address = "NONE", Status status = Status::active) :
		id{id}, name{ name }, phone_number{ phone_number }, address{ address }, status{ status } {}
	
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
};


