#pragma once
#include <string>
#include <initializer_list>
#include <vector>
#include <iosfwd>

namespace TB {
	using std::vector;
	using std::string;
	using list = std::initializer_list<std::string>;

	class Table{                    //mySQL처럼 출력하기 위한 클래스
	public:							//사용법: printHeader(), print(list), printTail()을 호출해야한다.
		void setFields(list ls);	//새로운 항목(id, name, price, address)등을 추가할 시 새 항목에 대한 최대 스트링 길이를 알아야 하므로 이 함수가 호출되어야 함
		void printHeader();
		void print(const list& contents);
		void printTail();
		Table(list field_names) : fields{ field_names.begin() ,field_names.end() } {}
	private:
		class Field {//출력할 필드들을 나타내는 클래스로 필드에 최대 스트링 길이를 기억한다
		public:
			Field(std::string name_);
			void check_field(std::string name_); //새로운 항목 최대 스트링 길이 검사
			const string getName() const { return name; }
			const unsigned int getLen() const { return max_len; }
		private:
			unsigned int max_len = 0;	//필드 최대 스트링 길이
			const std::string name;		//필드 이름
		};
		vector<Field> fields;
		void print_impl(char start, char pad);
		void print_impl(list contents, char start, char pad);
		void print_impl();
	};
}
