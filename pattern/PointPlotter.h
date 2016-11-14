#ifndef PLOT_H
#define PLOT_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QMessageBox>
#include <vector>
#include "Point.h"

class PointPlotter : public QMainWindow {
	Q_OBJECT
public:
	PointPlotter(std::vector<Point>);
	void createActions();
  void drawLines();
	void drawPoints();
	double getMax();
  static bool align(const Point &p1, const Point &p2);
protected:
  void resizeEvent(QResizeEvent *);
private slots:
	void brute();
	void fast();
	void quit();
private:
  struct Line {
    double x1, y1, x2, y2;
  };
	std::vector<Point> points;
  std::vector<Line> lines;
	QMenuBar *menuBar;
	QMenu *fileMenu;
	QAction *loadBrute;
	QAction *loadFast;
	QAction *exit;
  QGraphicsScene *scene;
  QGraphicsView *view;
};

#endif
