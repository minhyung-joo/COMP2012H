#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
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
 
  vector<Point> temp = points;
 
  while(!temp.empty()) {
    Point origin = temp.back();
		temp.pop_back();
    
		sort(temp.begin(), temp.end(), origin);
   
   int max = temp.size();
   max -= 2;
		for (int i = 0; i < max; i++) {
			double m1 = (temp[i].y - origin.y) / (temp[i].x - origin.x);
			double m2 = (temp[i+1].y - origin.y) / (temp[i+1].x - origin.x);
			double m3 = (temp[i+2].y - origin.y) / (temp[i+2].x - origin.x);
			
			if ( (m1 == m2) && (m2 == m3) ) {
        vector<Point> linePoints;
        int base = i;
        int count = 4;
        
        string msg;
        ostringstream stringStream;
        stringStream << "(" << origin.x << ", " << origin.y << ") ->";
        stringStream << "(" << temp[i].x << ", " << temp[i].y << ") ->";
				stringStream << "(" << temp[i+1].x << ", " << temp[i+1].y << ") ->";
				stringStream << "(" << temp[i+2].x << ", " << temp[i+2].y << ")";
				
				i += 3;
				while (i < temp.size()) {
					double tm = (temp[i].y - origin.y) / (temp[i].x - origin.x);
					if (m1 == tm) {
            stringStream << " -> (" << temp[i].x << ", " << temp[i].y << ")";
            linePoints.push_back(temp[i]);
            count++;
						i++;
					}
					else {
            i--; 
            break;
           }
				}
        temp.erase(temp.begin() + base, temp.begin() + i);
        
        char nums[4];
        sprintf(nums, "%d: ", count);
        msg = nums;
        msg += stringStream.str();
        cout << msg << endl;
        break;
			}
		}
	}
}
