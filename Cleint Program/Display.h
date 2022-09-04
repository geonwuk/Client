#pragma once
#include <string>
#include<initializer_list>
#include <vector>
#include <iostream>
using std::string;
using std::initializer_list;
class Query {
public:
	virtual void getInput() = 0;
};

template<typename C, typename T>
class print : public Query {
public:
	C c;
	T t;
	print(C c_, T t_) :t{ t_ }, c{ c_ } {}
	void getInput() {
		(c.*t)();
	}

};
template<typename C, typename T>
print<C,T> query(C c_,T t_) { return print<C,T>(c_, t_); }

//
//template<typename C, typename T>
//print<C, T> query2(C::T* t_) { return print<C, T>(c_, t_); }

class emptyQuery : public Query {
	void getInput() {
		std::cerr << "error" << std::endl;
	}
};

class Display{
public:
	Display(string text, Query& in) :text{ text }, in{ in } {} //const query&?
	Display(string text, Query&& in) :text{ text }, in{ in } {}
	Display(string text) :text{ text }, in{ empty } {}
	
	void addChild(initializer_list<Display*>);
	int run() const;
private:
	static emptyQuery empty;
	static Display nil;
	std::pair<int, bool> show(const Display&) const;
	Display(Query&& in= emptyQuery{}) : in{ in } {}

	void showMenu(const Display&) const;
	string text;
	Query& in;
	std::vector<Display*> childs;
};





