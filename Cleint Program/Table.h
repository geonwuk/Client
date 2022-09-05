#pragma once
#include <array>
#include <string>
#include <initializer_list>
namespace TB {
	class Field {
	public:
		Field(std::string name_) {
			operator=(name_);
		}
		Field& operator= (std::string name_) {
			auto sz = name_.size();
			max_len = max_len > sz ? max_len : sz;
			name = name_;
			return *this;
		}
		std::string getName() {
			return name;
		}
	private:
		unsigned int max_len;
		std::string name;
	};
	template<unsigned int N>
	class Table :public std::array<Field, N>{
	public:
		Table(std::initializer_list<string> names) {
			//template<unsigned int N>
			//struct Table :public std::array<Field, N> {
			//	template< typename X>
			//	Table(X x) : std::array<Field, N>{x } {}
			//};
			/*std::array<Field, N>::std::array<Field, N>(names);*/
		}

	private:
		std::array<Field, N> fields;
		void setField();
	};
}
