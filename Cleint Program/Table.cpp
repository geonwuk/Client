#include "Table.h"
#include <iomanip>
#include <iostream>
using namespace std;
using namespace TB;
Table::Field::Field(string name_) : name{ name_ } {	//생성 시 각 필드의 스트링 길이를 저장한다.
	auto sz = name_.size();
	max_len = max_len > sz ? max_len : sz;
}

void Table::Field::check_field(std::string name_){ //새롭게 원소가 추가될 떄 그 원소의 스트링 길이가 이전의 길이보다 긴 지 확인
	auto sz = name_.size();
	max_len = max_len > sz ? max_len : sz;
}

void TB::Table::setFields(list ls){
	auto itr = ls.begin();
	int i = 0;
	for (auto& field : fields) {
		field.check_field(itr[i++]);
	}
}

void TB::Table::printHeader() {
	print_impl('+', '-');
	print_impl();
	print_impl('+', '-');
}

void TB::Table::print(const list& contents) {
	print_impl(contents, '|', ' ');
}

void TB::Table::printTail() {
	print_impl('+', '-');
}

void TB::Table::print_impl(list contents, char start, char pad) {
	auto content = contents.begin();
	unsigned int idx = 0;
	for (auto f : fields) {
		cout << start << pad << std::setw(f.getLen()) << std::setfill(pad) << std::left << content[idx++] << pad;
	}
	cout << start << endl;
}

void TB::Table::print_impl(char start, char pad) {
	for (auto f : fields) {
		cout << start << pad << std::setw(f.getLen()) << std::setfill(pad) << "" << pad;
	}
	cout << start << endl;
}

void TB::Table::print_impl() {
	char start = '|';
	char pad = ' ';
	for (auto f : fields) {
		cout << start << pad << std::setw(f.getLen()) << std::setfill(pad) << std::left << f.getName() << pad;
	}
	cout << start << endl;
}
