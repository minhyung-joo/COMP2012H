#include <stdlib.h>
#include "Block.h"

Block::Block() {
  generateShape();
}

Block::Block(const Block &b) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      shape[i][j] = b.shape[i][j];
    }
  }
  cx = b.cx;
  cy = b.cy;
  type = b.type;
}

void Block::setCenterX(int x) {
  cx = x;
}

void Block::setCenterY(int y) {
  cy = y;
}

void Block::setShapeX(int index, int x) {
  shape[index][0] = x;
}

void Block::setShapeY(int index, int y) {
  shape[index][1] = y;
}

int Block::shapeX(int index) const {
  return shape[index][0];
}

int Block::shapeY(int index) const {
  return shape[index][1];
}

int Block::centerX() const {
  return cx;
}

int Block::centerY() const {
  return cy;
}

int Block::getType() const {
  return type;
}

/*
 * shape matrix heavily borrowed from Qt Tetrix example
 * link is included in the README.txt file
 */
void Block::generateShape() {
  static const int shapePool[7][4][2] = {
    { {0, -2}, {0, -1}, {0, 0}, {0, 1} }, // Type 1
    { {0, 1}, {0, 0}, {-1, 0}, {-1, 1} }, // Type 2
    { {0, -1}, {0, 0}, {1, 0}, {1, 1} }, // Type 3
    { {1, -1}, {1, 0}, {0, 0}, {0, 1} }, // Type 4
    { {0, -1}, {0, 0}, {0, 1}, {1, 1} }, // Type 5
    { {0, -1}, {0, 0}, {0, 1}, {-1, 1} }, // Type 6
    { {0, -1}, {0, 0}, {-1, 0}, {1, 0} } // Type 7
  };
  
  int r = rand() % 7;
  
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      shape[i][j] = shapePool[r][i][j];
    }
  }
  
  type = r + 1;
}
