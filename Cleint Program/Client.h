#pragma once
#include <string>
#include <iosfwd>

using std::string;

class Client{
public:
	enum class Status { active, resigend, dormant };

	Client(string name, string phone_number = "NONE", string address = "NONE", Status status = Status::active) :
		name{ name }, phone_number{ phone_number }, address{ address }, status{ status } {}
	
	void setName(string);
	void setPhoneNumber(string);
	void setAddress(string);


	string getName() const { return name; }
	string getPhoneNumber() const { return phone_number; }
	string getAddress() const { return address; }

	
private:
	

	unsigned int id;
	string ID;
	string name;
	string phone_number;
	string address;
	Status status;
};

std::ostream& operator<< (std::ostream& os, Client c);

