#include "ProductManager.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
using namespace PM;

unsigned int ProductManager::product_id=0;

std::ofstream& operator<< (std::ofstream& out, tm p) {//시간을 파일로 저장할 때 사용
	out << std::put_time(&p, "%A %c");
	return out;
}

std::ofstream& PM::operator<<(std::ofstream& out, const Product& p){ //CSV 파일 포맷으로 저장
	out << p.getId() << ',' << p.getName() << ',' << p.getPrice() << ',' << p.getQty()<<',';
	out << p.getDate();
	return out;
}


bool PM::operator== (const Product& p, const NoProduct&) { 
	//findProduct(id)에서 id에 해당하는 상품이 없으면 no_product를 리턴하는데 이를 확인할 때 사용
	const Product& np{ no_product };
	if (&p == &np)
		return true;
	else
		return false;
}

bool ProductManager::addProduct(const string name, const unsigned int price, const unsigned int qty, const std::tm local_time)
{
	bool success;
	tie(ignore, success) = products.emplace(product_id, Product{ product_id, name, price, qty, local_time });
	product_id++;
	return success;
}

bool ProductManager::eraseProduct(const unsigned int id){
	using int_type = decltype(products)::size_type;
	int_type success = products.erase(id);
	if (success == 1)
		return true;
	else
		return false;
}

const Product& ProductManager::findProduct(const unsigned int id) const{
	auto it = products.find(id);
	if (it == products.end()) {
		return no_product;
	}
	else {
		return it->second;
	}
}

const map<unsigned int, Product>& ProductManager::getProducts() const{
	return products;
}

const Product& PM::ProductManager::getProduct(const unsigned int id) const{
	auto p = products.find(id);
	if (p == products.end()) {
		return no_product;
	}
	else {
		return p->second;
	}
}

ofstream& PM::ProductManager::saveProducts(ofstream& out) const{
	for (const auto& p : products) {
		out << p.second << endl;
	}
	return out;
}

std::pair<std::ifstream&, std::vector<Product>> PM::ProductManager::loadProducts(ifstream& in){
	vector<Product> product_vector;
	std::string str;
	while (getline(in, str)){
		//한줄씩 실행
		vector<string> tmp;//, 사이에 있는 값들을 저장할 컨테이너
		auto begIdx = str.find_first_not_of(',');
		while (begIdx != string::npos) {//CSV 파일 포맷 파싱 중
			//한줄에 있는 , 수 만큼 반복합니다
			auto endIdx = str.find_first_of(',', begIdx);
			if (endIdx == string::npos) {
				endIdx = str.length();
			}
			tmp.emplace_back(str.substr(begIdx, endIdx - begIdx));
			begIdx = str.find_first_not_of(',', endIdx);
		}
		//csv파일 값 전달
		string time_string = tmp[4];
		unsigned int qty = stoul(tmp[3]);
		unsigned int price = stoul(tmp[2]);
		string name = tmp[1];
		unsigned int id = stoul(tmp[0]);

		tm time;
		istringstream ss{ time_string };
		ss >> std::get_time(&time, "%a %m/%d/%y %H:%M:%S");	//저장된 시간 파일 포맷
		product_vector.emplace_back(id, name, price, qty, time);
	}
	return  { in, move(product_vector) };
}

const unsigned int PM::ProductManager::getMaxIndex() const{
	return (--products.end())->first; //정렬된 맵을 활용
}