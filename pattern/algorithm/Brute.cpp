#include <iostream>
#include <vector>
#include "Point.h"
using namespace std;

int main() {
  int n;
	cin >> n;

	vector<Point> points;

	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		Point p = { x, y };
		points.push_back(p);
	}

  for (int i = 0; i < (n - 3); i++) {
		int x1 = points[i].x;
		int y1 = points[i].y;
		for (int j = (i + 1); j < (n - 2); j++) {
			int x2 = points[j].x;
			int y2 = points[j].y;
			for (int k = (j + 1); k < (n - 1); k++) {
				int x3 = points[k].x;
				int y3 = points[k].y;
				for (int l = (k + 1); l < n; l++) {
					int x4 = points[l].x;
					int y4 = points[l].y;
					
					double m1 = (double)(y2 - y1) / (double)(x2 - x1);
					double m2 = (double)(y3 - y1) / (double)(x3 - x1);
					double m3 = (double)(y4 - y1) / (double)(x4 - x1);

					if ( (m1 == m2) && (m2 == m3) ) {
            cout << "4: ";
            cout << "(" << x1 << ", " << y1 << ")" << " -> ";
						cout << "(" << x2 << ", " << y2 << ")" << " -> ";
						cout << "(" << x3 << ", " << y3 << ")" << " -> ";
						cout << "(" << x4 << ", " << y4 << ")" << endl;
					}
				}
			}
		}
	}
}
