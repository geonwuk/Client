#pragma once
#include <string>
#include <initializer_list>
#include <vector>
#include <iostream>

using std::string;
using std::initializer_list;
class Query {
	//상태패턴을 위한 인터페이스
public:
	virtual void getInput() = 0;
};

template<typename C, typename T>
class print : public Query {
	//상태패턴 인터페이스를 상속하여 구현하는 클래스
public:
	C c;//클래스 객체
	T t;//멤버 함수 포인터
	print(C c_, T t_) :t{ t_ }, c{ c_ } {}
	void getInput() {
		(c.*t)();
	}
};

//상태 패턴에 쓸 클래스를 생성하는 함수
template<typename C, typename T>
print<C,T> query(C c_,T t_) { return print<C,T>(c_, t_); }

class emptyQuery : public Query {
	//nil객체의 경우 getInput을 호출하지 않으므로 만약 호출될 경우를 대비해 "error"를 출력하도록 한다.
	void getInput() {
		std::cerr << "error" << std::endl;
	}
};

class Display{
public:
	Display(string text, Query&& in2) :text{ text }, in{ in2 } {}
	Display(string text) :text{ text }, in{ empty } {}
	
	void addChild(initializer_list<Display*>);//자식 노드 추가 함수
	int run() const;						  //메인함수에서 호출할 함수
private:
	static emptyQuery empty;    //nil객체가 갖는 query를 나타내는 객체
	static Display nil;         //가장 최상위 부모를 나타내는 노드 객체 
	std::pair<int, bool> show(const Display&) const;  //
	Display(Query&& in = emptyQuery{}) : in{ in } {}  //nil객체를 위한 생성자

	void showMenu(const Display&) const;  //자식 노드 수 만큼 메뉴를 보여준다.
	string text;                          //콘솔에 출력할 텍스트
	Query& in;                            //상태패턴 
	std::vector<Display*> childs;         //자식노드 배열
};





