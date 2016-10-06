#include <stdlib.h>
#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {
	LinkedList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.print();
	cout << "size: " << l.getSize() << endl;
	l.pop_front();
	l.pop_front();
	l.pop_front();
	l.print();
	cout << "size: " << l.getSize() << endl;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.print();
	cout << "size: " << l.getSize() << endl;
	l.pop_back();
	l.pop_back();
	l.pop_back();
	l.print();
	cout << "size: " << l.getSize() << endl;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.clear();
	l.print();
	cout << "size: " << l.getSize() << endl;
	system("pause");
	return 0;
}