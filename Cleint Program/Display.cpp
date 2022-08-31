#include "Display.h"

int Display::show() const
{
start:
	int selection;
	cout << text << endl;
	int i = 1;
	for (auto e = childs.begin(); e != childs.end(); e++) {
		cout << i++ << ". " << e->text<<" ";
	}
	cout << endl;
	cin >> selection;
	selection;
	if (selection <= 0)
		return -1;
	if (i > selection) {
		cout << selection << "은 선택 불가" << endl;
		goto start;
	}
	selection--;
	auto idx = childs.begin();
	(idx + selection)->show();
}
