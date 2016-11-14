#include <QGridLayout>
#include <stdlib.h>
#include <time.h>
#include "MainWindow.h"
#include "GameBoard.h"
#include "PreviewBoard.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  srand(time(NULL)); // seed only once in the program
  pBoard = new PreviewBoard(this);
  board = new GameBoard(this, pBoard);

  level = 1;
  score = 0;
  levelStr = QString("Level: %1").arg(level);
  scoreStr = QString("Score: %1").arg(score);
  levelLabel = new QLabel(levelStr);
  scoreLabel = new QLabel(scoreStr);

  // disable focus on all objects except for GameBoard
  // to ensure only GameBoard receives keyboard input
  setFocusPolicy(Qt::NoFocus);
  levelLabel->setFocusPolicy(Qt::NoFocus);
  scoreLabel->setFocusPolicy(Qt::NoFocus);
  pBoard->setFocusPolicy(Qt::NoFocus);
  
  QGridLayout *layout = new QGridLayout;
  layout->addWidget(board, 0, 0, 6, 2);
  layout->addWidget(pBoard, 2, 2, 2, 1);
  layout->addWidget(levelLabel, 4, 2, 1, 1);
  layout->addWidget(scoreLabel, 5, 2, 1, 1);

  connect(this, SIGNAL(levelUp(int)), board, SLOT(levelUp(int)));
  
  setLayout(layout);
  setWindowTitle(tr("Tetris"));
  resize(350, 420);
}

void MainWindow::start() {
  level = 1;
  score = 0;
  levelStr = QString("Level: %1").arg(level);
  scoreStr = QString("Score: %1").arg(score);
  levelLabel->setText(levelStr);
  scoreLabel->setText(scoreStr);
}

void MainWindow::scored(int combo) {
  int tlevel = 0;
  score += 10 * combo * combo;
  if (level < 10) {
    tlevel = (score / 100) + 1;
    if (tlevel > level) {
      level = tlevel;
      emit levelUp(level); // prompt GameBoard to speed up the game
    }
  }
  levelStr = QString("Level: %1").arg(level);
  scoreStr = QString("Score: %1").arg(score);
  levelLabel->setText(levelStr);
  scoreLabel->setText(scoreStr);
}
