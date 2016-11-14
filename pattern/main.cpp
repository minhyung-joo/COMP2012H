#include <iostream>
#include <fstream>
#include <QApplication>
#include <QVBoxLayout>
#include "PointPlotter.h"
using namespace std;

int main(int argc, char *argv[]) {
	char fileName[256];
	memset(fileName, 0, sizeof(fileName));
	if (argc < 2) {
		strcpy(fileName, "input.txt");
	}
	else {
		strcpy(fileName, argv[1]);
	}
	ifstream fs (fileName);
	if (!fs.good()) {
		cout << "Unable to open file: " << fileName << endl;
		return 0;
	}

	int n;
	fs >> n;

	vector<Point> points;
	for (int i = 0; i < n; i++) {
		int x, y;
		fs >> x;
		fs >> y;
		Point p = { x, y };
		points.push_back(p);
	}

	QApplication app(argc, argv);

	PointPlotter window(points);
	window.show();

	return app.exec();
}
