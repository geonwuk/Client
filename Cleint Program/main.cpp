#include<iostream>
#include<vector>
#include<algorithm>
#include"Client.h"
#include "ClientManager.h"
using namespace std;


int main() {
	vector<Client> client_list;


	client_list.emplace_back("Ken", "01012341234", "ABCABCABC");
	client_list.emplace_back("Ken2", "01022233333", "DEF");
	client_list.emplace_back("Ken3", "558887777", "1axcv");


	for_each(client_list.begin(), client_list.end(), [](Client c) {cout << c << endl; });
	bool go = true;

	do {
		int selection;
		cout << "���������α׷�" << endl;
		cout << "1. ����������" << endl;
		cout << "2. ��ǰ��������" << endl;
		cout << "3. ������������" << endl;
		cin >> selection;

		switch (selection)
		{
		case 1:
			


			break;
		case 2:

			break;
		case 3:

			break;


		default:
			break;
		}

	} while (go);


	cout << "hi" << endl;
}