#include <iostream>
#include "deque.h"
using namespace std;

int main() {
	Deque<char> d;
	char c;
	while (cin.get(c)) {
		if (isspace(c)) { break; }
		d.addFirst(c);
	}

	int max = d.size();
	if ((max % 2) != 0) {
		cout << "false" << endl;
		return 0;
	}
	for (int i = 0; i < max; i += 2) {
		char front = d.removeLast();
		char back = d.removeFirst();
		switch (front) {
			case 'A':
				front = 'T';
				break;
			case 'C':
				front = 'G';
				break;
			case 'T':
				front = 'A';
				break;
			case 'G':
				front = 'C';
				break;
		}
		if (front != back) {
			cout << "false" << endl;
			return 0;
		}
	}
	cout << "true" << endl;
}
