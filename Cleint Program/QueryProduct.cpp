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
		cout << "입력 오류입니다. 다시 입력하십시오. 숫자만 입력할 수 있습니다." << endl;
		goto again;
	}
	if (selection < 0) {
		cout << "입력 오류입니다. 다시 입력하십시오. 양수만 입력할 수 있습니다." << endl;
	}
	return selection;
}

void QueryProduct::QueryAddProduct(){
	time_t base_time = time(nullptr);	  //time(): 현재 시각을 리턴
	tm local_time;
	localtime_s(&local_time, &base_time); //localtime_s: 현재 시각을 local에 맞게 바꿔줌
	string name;			//제품이름
	unsigned int price;		//제품가격
	unsigned int qty;		//제품수량
	cout << "product name: ";
	cin.clear();				//입력버퍼 초기화
	cin.ignore(INT_MAX, '\n');	//입력버퍼 초기화
	getline(cin, name);			//이름받기
	cout << "price: ";
	price = getSelection();		//가격받기
	cout << "QTY: ";
	qty = getSelection();		//수량받기
	
	pm.addProduct(name, price, qty, local_time);	//ProductManager를 통해 제품 추가
	std::stringstream ss;
	ss<< std::put_time(&local_time, "%A %c");		//stringstream에 먼저 저장해야 스트링으로 저장 가능
	string time = ss.str();							//ss가 현재시각을 가지고 있으므로 time에 스트링으로 저장
	unsigned int id = pm.getMaxIndex();
	table.setFields({ to_string(id),name,to_string(price),to_string(qty),time });
}

void QueryProduct::QueryEraseProduct(){
	QueryShowProduct();
	unsigned int id;
	cout << "삭제할 상품 id: ";
	cin >> id;
	bool success = pm.eraseProduct(id);
	if (success) {
		cout << "ID:" << id << " 상품 삭제 완료" << endl;
	}
	else {
		cout << "ID:" << id << " 상품은 존재하지 않습니다. 삭제 실패" << endl;
	}
}
//TB::Table QueryProduct::table{ "id","name","price","quantity","date" };

void QueryProduct::QueryShowProduct()
{
	table.printHeader();
	auto m = pm.getProducts();
	for (auto& itr : m) {
		const Product& p = itr.second;
		std::stringstream ss;				//시간출력을 위한 준비
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
		pm.addProduct(i.getName(), i.getPrice(), i.getQty(), i.getDate());	//파일에 있는 값을 상품 목록에 추가한다
		unsigned int new_id = pm.getMaxIndex();
		std::stringstream ss;						//시간을 스트링으로 바꿀려면 스트림에서 받아야 한다.
		auto time_string = i.getDate();				//std::tm을 저장
		ss << std::put_time(&time_string, "%A %c");	//스트림에 원하는 포맷으로 저장
		string time = ss.str();						//스트림을 스트링으로 바꾼다
		table.setFields({ to_string(new_id),i.getName(), to_string(i.getPrice()), to_string(i.getQty()), time });
		//추가할 Product의 각 필드별(id, name, priec, ...)의 최대길이를 알기 위해 setFields를 호출한다
	}
}


