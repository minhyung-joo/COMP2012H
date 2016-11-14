#include <iostream>
#include <string>
#include "randomized_queue.h"
using namespace std;

// Removes whitespace from str
void trim(string& str) {
	for (int i = 0; i < str.length(); i++) {
		if (isspace(str.at(i))) {
			str.erase(i, 1);
			i--;
		}
	}
}

int main(int argc, char *argv[]) {
	srand(time(0));
	if (argc < 2) {
		cout << "Please specify an output number k!" << endl;
		return 0;
	}
	int k = atoi(argv[1]);

	RandomizedQueue<string> subset;
	string line;
	while (getline(cin, line, ' ')) {
		trim(line);
		subset.enqueue(line);
	}

	for (int i = 0; i < k; i++) {
		cout << subset.dequeue() << endl;
	}
}
