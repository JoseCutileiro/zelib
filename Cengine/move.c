#include "Cengine.h"
#include <stdio.h>

void move(int addedX, int addedY, Obj *obj, char map[screenH][screenW]){
  erase_shape((*obj).x, (*obj).y, (*obj).shape, map);
  draw_shape((*obj).x + addedX, (*obj).y + addedY, (*obj).shape, map);
  (*obj).x += addedX;
  (*obj).y += addedY;
}
