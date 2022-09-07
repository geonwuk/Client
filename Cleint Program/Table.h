#pragma once
#include <string>
#include <initializer_list>
#include <vector>
#include <iosfwd>

namespace TB {
	using std::vector;
	using std::string;
	using list = std::initializer_list<std::string>;

	class Table{                    //mySQLó�� ����ϱ� ���� Ŭ����
	public:							//����: printHeader(), print(list), printTail()�� ȣ���ؾ��Ѵ�.
		void setFields(list ls);	//���ο� �׸�(id, name, price, address)���� �߰��� �� �� �׸� ���� �ִ� ��Ʈ�� ���̸� �˾ƾ� �ϹǷ� �� �Լ��� ȣ��Ǿ�� ��
		void printHeader();
		void print(const list& contents);
		void printTail();
		Table(list field_names) : fields{ field_names.begin() ,field_names.end() } {}
	private:
		class Field {//����� �ʵ���� ��Ÿ���� Ŭ������ �ʵ忡 �ִ� ��Ʈ�� ���̸� ����Ѵ�
		public:
			Field(std::string name_);
			void check_field(std::string name_); //���ο� �׸� �ִ� ��Ʈ�� ���� �˻�
			const string getName() const { return name; }
			const unsigned int getLen() const { return max_len; }
		private:
			unsigned int max_len = 0;	//�ʵ� �ִ� ��Ʈ�� ����
			const std::string name;		//�ʵ� �̸�
		};
		vector<Field> fields;
		void print_impl(char start, char pad);
		void print_impl(list contents, char start, char pad);
		void print_impl();
	};
}
