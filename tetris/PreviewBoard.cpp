#include "PreviewBoard.h"

PreviewBoard::PreviewBoard(QWidget *parent) : QWidget(parent) {
  nextBlock = NULL;
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
}

void PreviewBoard::paintEvent(QPaintEvent *event) {
  painter = new QPainter(this);
  if (nextBlock) {
    int type = nextBlock->getType();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::black);
    
    int tx = 0;
    int ty = 0;
    int x = 2; // Approximate center of the PreviewBoard
    int y = 3;
    QColor orange(255, 153, 51);
    for (int i = 0; i < 4; i++) {
      tx = nextBlock->shapeX(i);
      ty = nextBlock->shapeY(i);
      switch (type) {
        case 1 :
          painter->fillRect((x + tx) * 20, (y + ty) * 20, 20, 20, Qt::red);
          break;
        case 2 :
          painter->fillRect((x + tx) * 20, (y + ty) * 20, 20, 20, Qt::green);
          break;
        case 3 :
          painter->fillRect((x + tx) * 20, (y + ty) * 20, 20, 20, Qt::blue);
          break;
        case 4 :
          painter->fillRect((x + tx) * 20, (y + ty) * 20, 20, 20, Qt::yellow);
          break;
        case 5 :
          painter->fillRect((x + tx) * 20, (y + ty) * 20, 20, 20, Qt::cyan);
          break;
        case 6 :
          painter->fillRect((x + tx) * 20, (y + ty) * 20, 20, 20, orange);
          break;
        case 7 :
          painter->fillRect((x + tx) * 20, (y + ty) * 20, 20, 20, Qt::magenta);
          break;
      }
      painter->drawRect((x + tx) * 20, (y + ty) * 20, 20, 20);
    }
  }
  
  delete painter;
}

Block* PreviewBoard::getNextBlock() {
  Block *pass = nextBlock;
  nextBlock = new Block;
  update();
  return pass;
}

void PreviewBoard::start() {
  delete nextBlock; // delete any remaining block from previous game
  nextBlock = new Block;
  update();
}
