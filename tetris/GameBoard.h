#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QPaintEvent>
#include "PreviewBoard.h"
#include "Block.h"

class GameBoard : public QWidget {
  Q_OBJECT
public:
  GameBoard(QWidget *, PreviewBoard *);
  void setBlockCenter();
  void keyPressEvent(QKeyEvent *);
  void paintEvent(QPaintEvent *);
  bool checkCollision(Block *);
  void moveRight();
  void moveLeft();
  void moveDown();
  void rotateRight();
  void rotateLeft();
  void checkLineClear();
  bool checkGameEnd();

public slots:
  void tick();
  void levelUp(int);

signals:
  void start();
  void lineClear(int);

private:
  int coord[20][10];
  QImage bgImage;
  QLabel background;
  QPainter *painter;
  QTimer *timer;
  Block *block;
  PreviewBoard *preview;
  bool playing;
};

#endif
