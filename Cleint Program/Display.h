#pragma once
#include <string>
#include <initializer_list>
#include <vector>
#include <iostream>

using std::string;
using std::initializer_list;
class Query {
	//���������� ���� �������̽�
public:
	virtual void getInput() = 0;
};

template<typename C, typename T>
class print : public Query {
	//�������� �������̽��� ����Ͽ� �����ϴ� Ŭ����
public:
	C c;//Ŭ���� ��ü
	T t;//��� �Լ� ������
	print(C c_, T t_) :t{ t_ }, c{ c_ } {}
	void getInput() {
		(c.*t)();
	}
};

//���� ���Ͽ� �� Ŭ������ �����ϴ� �Լ�
template<typename C, typename T>
print<C,T> query(C c_,T t_) { return print<C,T>(c_, t_); }

class emptyQuery : public Query {
	//nil��ü�� ��� getInput�� ȣ������ �����Ƿ� ���� ȣ��� ��츦 ����� "error"�� ����ϵ��� �Ѵ�.
	void getInput() {
		std::cerr << "error" << std::endl;
	}
};

class Display{
public:
	Display(string text, Query&& in2) :text{ text }, in{ in2 } {}
	Display(string text) :text{ text }, in{ empty } {}
	
	void addChild(initializer_list<Display*>);//�ڽ� ��� �߰� �Լ�
	int run() const;						  //�����Լ����� ȣ���� �Լ�
private:
	static emptyQuery empty;    //nil��ü�� ���� query�� ��Ÿ���� ��ü
	static Display nil;         //���� �ֻ��� �θ� ��Ÿ���� ��� ��ü 
	std::pair<int, bool> show(const Display&) const;  //
	Display(Query&& in = emptyQuery{}) : in{ in } {}  //nil��ü�� ���� ������

	void showMenu(const Display&) const;  //�ڽ� ��� �� ��ŭ �޴��� �����ش�.
	string text;                          //�ֿܼ� ����� �ؽ�Ʈ
	Query& in;                            //�������� 
	std::vector<Display*> childs;         //�ڽĳ�� �迭
};





