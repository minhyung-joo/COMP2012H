#include <QVBoxLayout>
#include "GameBoard.h"

GameBoard::GameBoard(QWidget *parent, PreviewBoard *pb) : QWidget(parent) {
  block = NULL;
  preview = pb;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      coord[i][j] = 0;
    }
  }
  connect(this, SIGNAL(start()), preview, SLOT(start()));
  connect(this, SIGNAL(start()), parent, SLOT(start()));
  connect(this, SIGNAL(lineClear(int)), parent, SLOT(scored(int)));
  playing = false;
  setFocusPolicy(Qt::StrongFocus);
  bgImage.load("background.bmp");
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
  setMaximumSize(200, 400);
}

/*
 * upon receiving block from PreviewBoard, change the
 * block coordinates to center it on the new board
 */
void GameBoard::setBlockCenter() {
  int type = block->getType();
  switch (type) {
    case 1 :
      block->setCenterX(4);
      block->setCenterY(2);
      break;
    case 2 :
      block->setCenterX(5);
      block->setCenterY(0);
      break;
    case 3 :
      block->setCenterX(4);
      block->setCenterY(1);
      break;
    case 4 :
      block->setCenterX(4);
      block->setCenterY(1);
      break;
    case 5 :
      block->setCenterX(4);
      block->setCenterY(1);
      break;
    case 6 :
      block->setCenterX(5);
      block->setCenterY(1);
      break;
    case 7 :
      block->setCenterX(4);
      block->setCenterY(1);
      break;
  }
}

void GameBoard::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Up) {
    if (!playing) {
      playing = true;
      for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
          coord[i][j] = 0;
        }
      }
      block = new Block;
      setBlockCenter();
      emit start();
      timer = new QTimer(this);
      connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
      timer->start(1000);
      update();
    }
  }
  // receive input only if the game is playing
  if (playing) {
    if (event->key() == Qt::Key_Down) {
      moveDown();
    }
    if (event->key() == Qt::Key_Left) {
      moveLeft();
    }
    if (event->key() == Qt::Key_Right) {
      moveRight();
    }
    if (event->key() == Qt::Key_Z) {
      rotateRight();
    }
    if (event->key() == Qt::Key_X) {
      rotateLeft();
    }
  }
}

void GameBoard::paintEvent(QPaintEvent *event) {
  painter = new QPainter(this);
  painter->eraseRect(0, 0, 400, 200);
  painter->drawImage(0, 0, bgImage);
  painter->setBrush(Qt::NoBrush);
  painter->setPen(Qt::black);
  QColor orange(255, 153, 51);

  // first paint the blocks already accumulated
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (coord[i][j] > 0) {
        switch (coord[i][j]) {
      	  case 1 :
      	    painter->fillRect(j * 20, i * 20, 20, 20, Qt::red);
      	    break;
      	  case 2 :
      	    painter->fillRect(j * 20, i * 20, 20, 20, Qt::green);
      	    break;
      	  case 3 :
      	    painter->fillRect(j * 20, i * 20, 20, 20, Qt::blue);
      	    break;
      	  case 4 :
      	    painter->fillRect(j * 20, i * 20, 20, 20, Qt::yellow);
      	    break;
      	  case 5 :
      	    painter->fillRect(j * 20, i * 20, 20, 20, Qt::cyan);
      	    break;
      	  case 6 :
      	    painter->fillRect(j * 20, i * 20, 20, 20, orange);
      	    break;
      	  case 7 :
      	    painter->fillRect(j * 20, i * 20, 20, 20, Qt::magenta);
      	    break;
      	}
	      painter->drawRect(j*20, i*20, 20, 20);
      }
    }
  }
  if (playing) {
    int tx = 0;
    int ty = 0;
    int type = block->getType();
    for (int i = 0; i < 4; i++) {
      tx = block->shapeX(i) + block->centerX();
      ty = block->shapeY(i) + block->centerY();
      switch (type) {
	case 1 :
	  painter->fillRect(tx * 20, ty * 20, 20, 20, Qt::red);
	  break;
	case 2 :
	  painter->fillRect(tx * 20, ty * 20, 20, 20, Qt::green);
	  break;
	case 3 :
	  painter->fillRect(tx * 20, ty * 20, 20, 20, Qt::blue);
	  break;
	case 4 :
	  painter->fillRect(tx * 20, ty * 20, 20, 20, Qt::yellow);
	  break;
	case 5 :
	  painter->fillRect(tx * 20, ty * 20, 20, 20, Qt::cyan);
	  break;
	case 6 :
	  painter->fillRect(tx * 20, ty * 20, 20, 20, orange);
	  break;
	case 7 :
	  painter->fillRect(tx * 20, ty * 20, 20, 20, Qt::magenta);
	  break;
      }
      painter->drawRect(tx * 20, ty * 20, 20, 20);
    }
  }
  delete painter;
}

void GameBoard::tick() {
  Block temp = *block;
  temp.setCenterY(block->centerY() + 1);
  if (!checkCollision(&temp)) {
    block->setCenterY(block->centerY() + 1);
    update();
  }
  else {
      int type = block->getType();
      int tx = 0;
      int ty = 0;
      for (int i = 0; i < 4; i++) {
        tx = block->centerX() + block->shapeX(i);
        ty = block->centerY() + block->shapeY(i);
        coord[ty][tx] = type;
      }
      delete block; // delete block once it is recorded in the coordinate system
      if (!checkGameEnd()) {
        block = preview->getNextBlock();
        setBlockCenter();
        checkLineClear();
        update();
      }
    
  }
}

void GameBoard::levelUp(int level) {
  timer->setInterval(1000 - (100 * (level - 1)));
}

bool GameBoard::checkCollision(Block *block) {
  int check = 0;
  
  int tx = 0;
  int ty = 0;
  int cx = block->centerX();
  int cy = block->centerY();
  
  // check for every square if there is a
  // block present in the new coordinates
  for (int i = 0; i < 4; i++) {
    tx = cx + block->shapeX(i);
    ty = cy + block->shapeY(i);
    if (tx >= 0 && tx < 10 && ty >= 0 && ty < 20) {
      if (coord[ty][tx] == 0) { check++; }
    }
  }
  
  if (check == 4) { return false; }
  else { return true; }
}

void GameBoard::moveRight() {
  Block temp = *block;
  temp.setCenterX(temp.centerX() + 1);
  if (!checkCollision(&temp)) {
    block->setCenterX(block->centerX() + 1);
    update();
  }
}

void GameBoard::moveLeft() {
  Block temp = *block;
  temp.setCenterX(temp.centerX() - 1);
  if (!checkCollision(&temp)) {
    block->setCenterX(block->centerX() - 1);
    update();
  }
}

void GameBoard::moveDown() {
  Block temp = *block;
  temp.setCenterY(temp.centerY() + 1);
  if (!checkCollision(&temp)) {
    block->setCenterY(block->centerY() + 1);
    update();
  }
}

/*
 * rotation algorithms heavily borrowed from the Qt Tetrix example
 * in the qt documentation. Link is included in README.txt
 */
void GameBoard::rotateRight() {
  Block temp = *block;
  for (int i = 0; i < 4; ++i) {
    int rx = temp.shapeX(i);
    int ry = temp.shapeY(i);
    temp.setShapeX(i, -ry);
    temp.setShapeY(i, rx);
  }
  
  if (!checkCollision(&temp)) {
    for (int i = 0; i < 4; ++i) {
      int rx = block->shapeX(i);
      int ry = block->shapeY(i);
      block->setShapeX(i, -ry);
      block->setShapeY(i, rx);
    }
    
    update();
  }
}

void GameBoard::rotateLeft() {
  Block temp = *block;
  for (int i = 0; i < 4; ++i) {
    int rx = temp.shapeX(i);
    int ry = temp.shapeY(i);
    temp.setShapeX(i, ry);
    temp.setShapeY(i, -rx);
  }
  
  if (!checkCollision(&temp)) {
    for (int i = 0; i < 4; ++i) {
      int rx = block->shapeX(i);
      int ry = block->shapeY(i);
      block->setShapeX(i, ry);
      block->setShapeY(i, -rx);
    }
    
    update();
  }
}

void GameBoard::checkLineClear() {
  int combo = 0;
  for (int i = 0; i < 20; i++) {
    int check = 0;
    for (int j = 0; j < 10; j++) {
      if (coord[i][j] > 0) { check++; }
    }
    if (check == 10) {
      combo++;
      for (int y = (i - 1); y >= 0; y--) {
        for (int x = 0; x < 10; x++) {
          coord[y+1][x] = coord[y][x];
        }
      }
    }
  }
  emit lineClear(combo); // prompt MainWindow to update score and level
}

bool GameBoard::checkGameEnd() {
  int check = 0;

  // check only the top two rows
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 10; j++) {
      if (coord[i][j] > 0) { check++; }
    }
  }
  if (check > 0) {
    playing = false;
    timer->stop();
    delete timer;
    update();
    return true;
  }
  else return false;
}
