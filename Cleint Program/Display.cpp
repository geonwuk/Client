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

static int getSelection() {
again:
	int selection;
	try {
		cin >> selection;
	}
	catch (const std::ios_base::failure&) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "�Է� �����Դϴ�. �ٽ� �Է��Ͻʽÿ�. ���ڸ� �Է��� �� �ֽ��ϴ�." << endl;
		goto again;
	}
	return selection;
}

std::pair<int, bool> Display::show(const Display& parent) const
{
	int selection;
start:
	system("cls");
	cout << text << endl;
	if (childs.empty()) {
		in.getInput();
		cout << endl;
		cout << parent.text << endl;
		showMenu(parent);
		selection = getSelection();
		return { selection,true };
	}
	showMenu(*this);
	selection = getSelection();
middle:
	if (selection <= 0)
		return { -1,false };
	if (selection > static_cast<int>(childs.size())) {
		system("cls");
		cout << selection << "�� ���� �Ұ�" << endl<<endl;
		showMenu(*this);
		selection = getSelection();
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
