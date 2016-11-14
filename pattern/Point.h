#ifndef POINT_H
#define POINT_H

class Point {
public:
	double x, y;
  bool operator() (const Point &p1, const Point &p2) {
      double m1 = (p1.y - y) / (p1.x - x);
      double m2 = (p2.y - y) / (p2.x - x);
  
      return m1 < m2;
    }
};

#endif
