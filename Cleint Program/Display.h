#pragma once
#include <string>
#include <iostream>
#include<initializer_list>
using std::string;
using std::initializer_list;
using std::cout;
using std::endl;
using std::cin;
class Display{
public:
	Display(string text, initializer_list<Display> childs = {}) : text{ text }, childs{ childs }{}
	
	int show() const;

	string text;
private:
	initializer_list<Display> childs;
};

