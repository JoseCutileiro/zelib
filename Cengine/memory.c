#include "Cengine.h"
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void cube(SPRITES memory,int index){
  memory[index].size = 169;
  memory[index].sqrt_size = 13;
  memory[index].info = ",,,+--------+,,/        /|,/        / |+--------+  ||        |  ||        |  +|        | / |        |/  +--------+   ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,";
}


void merda(SPRITES memory, int index) {
  memory[index].size = 16;
  memory[index].sqrt_size = 4;
  memory[index].info = "+++++:)+++++";
}


void addObj(OBJ memory,Sprite shape,int *numberOfObjs,int x,int y){
  int index = *numberOfObjs;

  if (*numberOfObjs%10 == 0) {
    memory = realloc(memory,sizeof(Obj)*(*numberOfObjs + 10));
  }

  memory[index].x = x;
  memory[index].y = y;
  memory[index].objId = *numberOfObjs;
  memory[index].shape = shape;
  *numberOfObjs+=1;
}

SPRITES init_memory_sprites(){
  int numberOfSprites = 2;
  SPRITES ret = malloc(sizeof(Sprite) * (numberOfSprites +10));
  cube(ret,0);
  merda(ret, 1);
  return ret;
}

OBJ init_memory_obj(){
  int var = 0;
  SPRITES r = init_memory_sprites();
  Sprite r0 = r[0];
  Sprite r1 = r[1];
  OBJ ret = malloc(sizeof(Obj)*10);
  int i,j;
  for (i = 0; i < 10;i++){
    for (j = 0; j < 10; j++){
      addObj(ret, r0, &var, rand()%600, rand()%100);
    }
  }

  addObj(ret, r1, &var, 1, 1);
  return ret;
}
