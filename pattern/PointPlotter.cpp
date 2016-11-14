#include <iostream>
#include <string>
#include <sstream>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QElapsedTimer>
#include <QString>
#include "PointPlotter.h"
using namespace std;

bool PointPlotter::align(const Point &p1, const Point &p2) {
  return p1.x < p2.x;
}

PointPlotter::PointPlotter(std::vector<Point> v) {
	points = v;

	createActions();

	menuBar = new QMenuBar(this);
	fileMenu = new QMenu("File");
	fileMenu->addAction(loadBrute);
	fileMenu->addAction(loadFast);
	fileMenu->addAction(exit);
	menuBar->addMenu(fileMenu);
 
	//board = new PlotBoard(this, getMax());
  scene = new QGraphicsScene();
  view = new QGraphicsView(scene, this);
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setCentralWidget(view);
	setMenuBar(menuBar);
	resize(500, 500);
	setWindowTitle("Point Plotter");
	drawPoints();
}

void PointPlotter::resizeEvent(QResizeEvent *) {
	scene->clear();
  
	drawPoints();
  drawLines();
}

void PointPlotter::brute() {
  lines.clear();

  QElapsedTimer timer;
  timer.start();

  int n = points.size();
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

            vector<Point> temp;
            temp.push_back(points[i]);
            temp.push_back(points[j]);
            temp.push_back(points[k]);
            temp.push_back(points[l]);
            
            sort(temp.begin(), temp.end(), align);
            
            Line l = { temp[0].x, temp[0].y, temp[3].x, temp[3].y };
            lines.push_back(l);
            drawLines();
					}
				}
			}
		}
	}
  int t = timer.elapsed();
  QString msg;
  msg.setNum(t);
  msg += " msec";
  QMessageBox msgBox(QMessageBox::NoIcon, "Time used", msg, QMessageBox::Ok, this);
  msgBox.exec();
}

void PointPlotter::fast() {
  lines.clear();
  
  vector<Point> temp = points;
  
  QElapsedTimer timer;
  timer.start();
  
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
				
        linePoints.push_back(origin);
        linePoints.push_back(temp[i]);
        linePoints.push_back(temp[i+1]);
        linePoints.push_back(temp[i+2]);
        
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
        
        int last = linePoints.size() - 1;
        sort(linePoints.begin(), linePoints.end(), align);
        Line l = { linePoints[0].x, linePoints[0].y, linePoints[last].x, linePoints[last].y };
        lines.push_back(l);
        drawLines();
        
        char nums[4];
        sprintf(nums, "%d: ", count);
        msg = nums;
        msg += stringStream.str();
        cout << msg << endl;
        break;
			}
		}
	}
 
  int t = timer.elapsed();
  QString msg;
  msg.setNum(t);
  msg += " msec";
  QMessageBox msgBox(QMessageBox::NoIcon, "Time used", msg, QMessageBox::Ok, this);
  msgBox.exec();
}

void PointPlotter::quit() {
  QApplication::quit();
}

void PointPlotter::drawLines() {
  double max = getMax();
	double width = rect().width() - (rect().width() / 10);
	double height = rect().height() - (rect().height() / 10);
  for (int i = 0; i < lines.size(); i++) {
    Line l = lines[i];
    double x1 = ((l.x1 / max) * width);
    double y1 = (height - (l.y1 / max) * height);
    double x2 = ((l.x2 / max) * width);
    double y2 = (height - (l.y2 / max) * height);
    
    QGraphicsLineItem *line = new QGraphicsLineItem(x1, y1, x2, y2);
    scene->addItem(line);
  }
}

void PointPlotter::createActions() {
	loadBrute = new QAction("Load brute algo", this);
	loadFast = new QAction("Load fast algo", this);
	exit = new QAction("Exit", this);

	connect(loadBrute, SIGNAL(triggered()), this, SLOT(brute()));
	connect(loadFast, SIGNAL(triggered()), this, SLOT(fast()));
	connect(exit, SIGNAL(triggered()), this, SLOT(quit()));
}

void PointPlotter::drawPoints() {
	double max = getMax();
	double width = rect().width() - (rect().width() / 10);
	double height = rect().height() - (rect().height() / 10);
	for (int i = 0; i < points.size(); i++) {
		double x = ((points[i].x / max) * width);
		double y = (height - (points[i].y / max) * height);
   
		QGraphicsEllipseItem *p = new QGraphicsEllipseItem(x-3, y-3, 6, 6);
		scene->addItem(p);
	}
}

double PointPlotter::getMax() {
	double max = 0;

	for (int i = 0; i < points.size(); i++) {
		double tx = points[i].x;
		double ty = points[i].y;
		if (tx > max) {
			max = tx;
		}
		if (ty > max) {
			max = ty;
		}
	}

	return max;
}
