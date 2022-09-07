#include "Display.h"
#include <windows.h>
#include <tuple>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
emptyQuery Display::empty{};  //nil��ü�� ���� query�� ��Ÿ���� ��ü
Display Display::nil{ };      //���� �ֻ��� �θ� ��Ÿ���� ��� ��ü 
void Display::showMenu(const Display& disp) const {
	//�ڽ� ��� �� ��ŭ �޴��� �����ش�.
	int i = 1;
	for (auto e : disp.childs) {
		cout << i++ << ". " << e->text << endl;
	}
}

void Display::addChild(initializer_list<Display*> d){
	//�ڽ� ��带 �߰��ϴ� �Լ�
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
	//���� �ܿ� ���ڸ� �Է����� �� �ٽ� �Է��ϵ��� ó���ϴ� �Լ�
again:
	int selection;
	try {
		cin >> selection;
	}
	catch (const std::ios_base::failure&) {
		//clear, ignore�� ���� �ٽ� �Է��� ���� �� �ְ� cin�� �ʱ�ȭ�ϰ� goto�� �ٽ� �Է��� �޴´�.
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "�Է� �����Դϴ�. �ٽ� �Է��Ͻʽÿ�. ���ڸ� �Է��� �� �ֽ��ϴ�." << endl;
		goto again;
	}
	return selection;
}

std::pair<int, bool> Display::show(const Display& parent) const{
	//��� ������ ���� Ʈ�������� ��ȸ�Ѵ�
	int selection;
start:
	system("cls");
	cout << text << endl;
	if (childs.empty()) {	//��� Ż�� ����: �ڽĳ�尡 ���� ������ ����� ���
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
	if (selection <= 0) //����ڰ� 0�̳� ������ �Է��ϸ� �����Ѵ� (�ڷ� ����)
		return { -1,false };
	if (selection > static_cast<int>(childs.size())) { //����ڰ� ���� ��ȣ���� �� ũ�� �Է��� ��� ���� ó��
		system("cls");
		cout << selection << "�� ���� �Ұ�" << endl<<endl;
		showMenu(*this);
		selection = getSelection();
		goto middle;								   //middle�� ���� �ٽ� �Է��� �ް� �Ѵ�
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
