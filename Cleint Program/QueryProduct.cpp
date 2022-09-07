#include "QueryProduct.h"
#include <iostream>
#include<ctime>
#include  <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
using namespace std;
using namespace PM;
TB::Table QueryProduct::table{ "id","name","price","quantity","date"};

static int getSelection() {
again:
	int selection;
	try {
		cin >> selection;
	}
	catch (const std::ios_base::failure&) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "�Է� �����Դϴ�. �ٽ� �Է��Ͻʽÿ�. ���ڸ� �Է��� �� �ֽ��ϴ�." << endl;
		goto again;
	}
	if (selection < 0) {
		cout << "�Է� �����Դϴ�. �ٽ� �Է��Ͻʽÿ�. ����� �Է��� �� �ֽ��ϴ�." << endl;
	}
	return selection;
}

void QueryProduct::QueryAddProduct(){
	time_t base_time = time(nullptr);	  //time(): ���� �ð��� ����
	tm local_time;
	localtime_s(&local_time, &base_time); //localtime_s: ���� �ð��� local�� �°� �ٲ���
	string name;			//��ǰ�̸�
	unsigned int price;		//��ǰ����
	unsigned int qty;		//��ǰ����
	cout << "product name: ";
	cin.clear();				//�Է¹��� �ʱ�ȭ
	cin.ignore(INT_MAX, '\n');	//�Է¹��� �ʱ�ȭ
	getline(cin, name);			//�̸��ޱ�
	cout << "price: ";
	price = getSelection();		//���ݹޱ�
	cout << "QTY: ";
	qty = getSelection();		//�����ޱ�
	
	pm.addProduct(name, price, qty, local_time);	//ProductManager�� ���� ��ǰ �߰�
	std::stringstream ss;
	ss<< std::put_time(&local_time, "%A %c");		//stringstream�� ���� �����ؾ� ��Ʈ������ ���� ����
	string time = ss.str();							//ss�� ����ð��� ������ �����Ƿ� time�� ��Ʈ������ ����
	unsigned int id = pm.getMaxIndex();
	table.setFields({ to_string(id),name,to_string(price),to_string(qty),time });
}

void QueryProduct::QueryEraseProduct(){
	QueryShowProduct();
	unsigned int id;
	cout << "������ ��ǰ id: ";
	cin >> id;
	bool success = pm.eraseProduct(id);
	if (success) {
		cout << "ID:" << id << " ��ǰ ���� �Ϸ�" << endl;
	}
	else {
		cout << "ID:" << id << " ��ǰ�� �������� �ʽ��ϴ�. ���� ����" << endl;
	}
}
//TB::Table QueryProduct::table{ "id","name","price","quantity","date" };

void QueryProduct::QueryShowProduct()
{
	table.printHeader();
	auto m = pm.getProducts();
	for (auto& itr : m) {
		const Product& p = itr.second;
		std::stringstream ss;				//�ð������ ���� �غ�
		auto t = p.getDate();
		ss << std::put_time(&t, "%A %c");
		string time = ss.str();
		table.print({ std::to_string(p.getId()), p.getName(), to_string(p.getPrice()), to_string(p.getQty()), time });
	}
	table.printTail();
}

void QueryProduct::QuerySaveProduct(){
	std::ofstream out("Product.txt");
	pm.saveProducts(out);
}

void QueryProduct::QueryLoadProduct()
{
	std::ifstream in{ "Product.txt" };
	auto pr = pm.loadProducts(in);

	for (auto& i : pr.second) {
		pm.addProduct(i.getName(), i.getPrice(), i.getQty(), i.getDate());	//���Ͽ� �ִ� ���� ��ǰ ��Ͽ� �߰��Ѵ�
		unsigned int new_id = pm.getMaxIndex();
		std::stringstream ss;						//�ð��� ��Ʈ������ �ٲܷ��� ��Ʈ������ �޾ƾ� �Ѵ�.
		auto time_string = i.getDate();				//std::tm�� ����
		ss << std::put_time(&time_string, "%A %c");	//��Ʈ���� ���ϴ� �������� ����
		string time = ss.str();						//��Ʈ���� ��Ʈ������ �ٲ۴�
		table.setFields({ to_string(new_id),i.getName(), to_string(i.getPrice()), to_string(i.getQty()), time });
		//�߰��� Product�� �� �ʵ庰(id, name, priec, ...)�� �ִ���̸� �˱� ���� setFields�� ȣ���Ѵ�
	}
}


