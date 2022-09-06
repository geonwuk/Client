#pragma once
#include <array>
#include <string>
#include <initializer_list>
#include <vector>
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::vector;
using std::string;
namespace TB {
	using list = std::initializer_list<std::string>;
	class Field {
	public:
		Field(std::string name_);
		void check_field(std::string name_);
		string getName() const { return name; }
		const unsigned int getLen() const {return max_len; }
	private:
		unsigned int max_len=0;
		const std::string name;
	};
	class Table{
	public:
		Table() {}
		void setFields(list ls);
		void print_header();
		void print(const list& contents);
		void print_tail();
		Table(list field_names) : fields{ field_names.begin() ,field_names.end() } {}
	private:
		vector<Field> fields;
		void print_impl(list contents, char start, char pad);
		void print_impl();
	};
}
