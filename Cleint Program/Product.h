#pragma once
#include <string>
#include <ctime>

using std::string;
class Product
{
public:
	Product(unsigned int id, string ID, string name, double price, double discounted_ratio, tm date):
		id{ id }, ID{ ID }, name{ name }, price{ price }, discounted_ratio{ discounted_ratio }, registered_date{ date }{}

	const unsigned int getId() const { return id; }

	unsigned int id;
	string ID;
	string name;
	double price;
	double discounted_ratio;
	tm registered_date;

	

};