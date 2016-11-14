#ifndef BLOCK_H
#define BLOCK_H

class Block {
public:
  Block();
  Block(const Block &b);
  void setCenterX(int);
  void setCenterY(int);
  void setShapeX(int, int);
  void setShapeY(int, int);
  int shapeX(int) const;
  int shapeY(int) const;
  int centerX() const;
  int centerY() const;
  int getType() const;
  void generateShape();
private:
  int shape[4][2];
  int cx;
  int cy;
  int type;
};

#endif