#include "Cengine.h"
#include "memory.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define EXIT '_'

void update(char map[screenH][screenW], OBJ memory,int objsInMemory,SPRITES memory_sprites){
  int i;
  for (i = 0; i < objsInMemory; i++) {
    move(0,0 ,&(memory[i]), map);
  }
  move(4,0,&(memory[100]),map);

  
}

int main() {
  srand(time(NULL));
  SPRITES memory_sprites = init_memory_sprites();
  OBJ memory_obj = init_memory_obj();
  int objsInMemory = 101;
  char map[screenH][screenW];
  char key = '+';
  init_map(map);

  while (key != EXIT) {
    print_map(map);
    update(map, memory_obj, objsInMemory,memory_sprites);
    delay(20000);
    key = buffer_delete();
  }
}

