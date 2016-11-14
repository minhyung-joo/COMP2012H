#ifndef PREV_H
#define PREV_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include "Block.h"

class PreviewBoard : public QWidget {
  Q_OBJECT
public:
  PreviewBoard(QWidget *);
  void paintEvent(QPaintEvent *);
  Block* getNextBlock();
public slots:
  void start();
private:
  QPainter *painter;
  Block *nextBlock;
};

#endif