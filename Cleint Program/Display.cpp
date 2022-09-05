#include "Display.h"
#include <windows.h>
#include <tuple>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
emptyQuery Display::empty{};
Display Display::nil{};
void Display::showMenu(const Display& disp) const {
	int i = 1;
	for (auto e : disp.childs) {
		cout << i++ << ". " << e->text << endl;
	}
}

void Display::addChild(initializer_list<Display*> d)
{
	for (auto i : d) {
		childs.push_back(&(*i));
	}
}

int Display::run() const
{
	show(nil);
	return -1;
}

std::pair<int, bool> Display::show(const Display& parent) const
{
	int selection;
start:
	system("cls");
	if (childs.empty()) {
		in.getInput();
		cout << endl;
		showMenu(parent);
		cin >> selection;
		return { selection,true };
	}
	cout << text << endl;
	showMenu(*this);
	cin >> selection;
middle:
	if (selection <= 0)
		return { -1,false };
	if (selection > static_cast<int>(childs.size())) {
		system("cls");
		cout << selection << "은 선택 불가" << endl<<endl;
		showMenu(*this);
		cin >> selection;
		goto middle;
	}
	//test
	--selection;
	bool last_child;
	std::tie(selection, last_child) = childs[selection]->show(*this);
	if (last_child)
		goto middle;
	else
		goto start;
}
