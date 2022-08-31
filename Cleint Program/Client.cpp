#include "Client.h"
#include <iostream>

using namespace std;

ostream& operator<< (ostream& os, Client c) {
	cout << "Name: " << c.getName() << endl;
	cout << "Phone: " << c.getPhoneNumber() << endl;
	cout << "Address: " << c.getAddress() << endl;
	return os;
}