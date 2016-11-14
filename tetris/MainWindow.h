#ifndef MAIN_H
#define MAIN_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QTimer>
#include <QKeyEvent>
#include "GameBoard.h"
#include "PreviewBoard.h"

class MainWindow : public QWidget {
  Q_OBJECT
public:
  MainWindow(QWidget *parent=0);
public slots:
  void start();
  void scored(int);
signals:
  void levelUp(int);
private:
  GameBoard *board;
  PreviewBoard *pBoard;
  QLabel *levelLabel;
  QLabel *scoreLabel;
  QString levelStr;
  QString scoreStr;
  int level;
  int score;
};

#endif