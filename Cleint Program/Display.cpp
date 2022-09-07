#include "Display.h"
#include <windows.h>
#include <tuple>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
emptyQuery Display::empty{};  //nil객체가 갖는 query를 나타내는 객체
Display Display::nil{ };      //가장 최상위 부모를 나타내는 노드 객체 
void Display::showMenu(const Display& disp) const {
	//자식 노드 수 만큼 메뉴를 보여준다.
	int i = 1;
	for (auto e : disp.childs) {
		cout << i++ << ". " << e->text << endl;
	}
}

void Display::addChild(initializer_list<Display*> d){
	//자식 노드를 추가하는 함수
	for (auto i : d) {
		childs.emplace_back(&(*i));
	}
}

int Display::run() const{
	//
	show(nil);
	return -1;
}

static int getSelection() {
	//숫자 외에 문자를 입력했을 때 다시 입력하도록 처리하는 함수
again:
	int selection;
	try {
		cin >> selection;
	}
	catch (const std::ios_base::failure&) {
		//clear, ignore를 통해 다시 입력을 받을 수 있게 cin을 초기화하고 goto로 다시 입력을 받는다.
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "입력 오류입니다. 다시 입력하십시오. 숫자만 입력할 수 있습니다." << endl;
		goto again;
	}
	return selection;
}

std::pair<int, bool> Display::show(const Display& parent) const{
	//재귀 구조를 통해 트리구조를 순회한다
	int selection;
start:
	system("cls");
	cout << text << endl;
	if (childs.empty()) {	//재귀 탈출 조건: 자식노드가 없는 마지막 노드인 경우
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
	if (selection <= 0) //사용자가 0이나 음수를 입력하면 리턴한다 (뒤로 가기)
		return { -1,false };
	if (selection > static_cast<int>(childs.size())) { //사용자가 선택 번호보다 더 크게 입력할 경우 에러 처리
		system("cls");
		cout << selection << "은 선택 불가" << endl<<endl;
		showMenu(*this);
		selection = getSelection();
		goto middle;								   //middle로 가서 다시 입력을 받게 한다
	}
	selection = selection - 1;
	int last_selection = selection;
	bool last_child;
	std::tie(selection, last_child) = childs[last_selection]->show(*this);
	if (last_child)
		goto middle;
	else
		goto start;
}
