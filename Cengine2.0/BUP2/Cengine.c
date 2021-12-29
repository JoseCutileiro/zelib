#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "Cengine.h"
#include "Sprites.h"
#include <string.h>
#include <time.h>



/* GLOBAL VARS */ 

// 1) general behaviour

char key; // Player input
char frame[screenH][screenW];


// 2) table allocation and handling

int* available_spr_i;
int* available_obj_i;
Sprite* sprite_table; // 1 > available
Obj* obj_table;       // 0 > unavailable
int spr_table_size;
int obj_table_size;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Frame funtions:                                                                                                               //
// A full setup to work with the frame itself                                                                                    //
// [UNIQUE FRAME != CAMERA MODE]                                                                                                 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_frame() {
  for (int i = 0; i < screenH; i++) {
    for (int j = 0; j < screenW; j++) {
      if (j == screenW - 1) {
        frame[i][j] = ENDLINE;
        continue;
      }
      /*
      if (j == screenW - 2) {
        frame[i][j] = NEXTLINE;
        continue;
      }
      */
      if (j == 0 || j == screenW - 2 || i == 0 || i == screenH -1) {
        frame[i][j] = PIXEL;
        continue;
      }
      frame[i][j] = SPACE;

      
    }
  }
}

void print_frame() {
  for (int i = 0; i < screenH; i++) {
    printf("%s\n",frame[i]);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sprite funtions:                                                                                                              //
// Work with your sprites more easily using this funtions                                                                        //
// [SINGULAR SPRS]                                                                                                               // 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Sprite init_sprite(char str[],int witdth,int height) {
  Sprite new_spr;
  new_spr.info = (char*) malloc(sizeof(char) * (witdth * height + 1));
  strcpy(new_spr.info,str);
  new_spr.hei = height;
  new_spr.wid = witdth;
  return new_spr;
}

void update_sprite(Obj obj,char NEW_str[]) {
  strcpy(obj.sprite.info,NEW_str);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Object funtions:                                                                                                              //
// Work with your objects more easily using this funtions                                                                        //
// [SINGULAR OBJS]                                                                                                               // 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Obj create_obj(Sprite sprite,int X,int Y) {
  Obj new_obj;
  new_obj.sprite = sprite;
  new_obj.ogX = X;
  new_obj.ogY = Y;
  return new_obj;
}

void draw_obj(Obj obj) {
  int x = obj.ogX;
  int y = obj.ogY;
  int w = obj.sprite.wid + x;
  int h = obj.sprite.hei + y;
  int iter = -1;
  for (int i = y; i < h; i++) {
    for (int j = x; j < w; j++) {
      iter ++;
      if (j >= screenW - 2 || j <= 0 ||  i >= screenH - 1 || i <= 0) {
        continue;
      }
      if (obj.sprite.info[iter] == VOID) {
        continue;
      }
      frame[i][j] = obj.sprite.info[iter];
    }
  }
}

void erase_obj(Obj obj) {
  int x = obj.ogX;
  int y = obj.ogY;
  int w = obj.sprite.wid + x;
  int h = obj.sprite.hei + y;
  int iter = -1;
  for (int i = y; i < h; i++) {
    for (int j = x; j < w; j++) {
      iter ++;
      if (j >= screenW - 2 || j <= 0 ||  i >= screenH - 1 || i <= 0) {
        continue;
      }
      if (obj.sprite.info[iter] == VOID) {
        continue;
      }
      frame[i][j] = ' ';
    }
  }
}

void move_obj(int addedX,int addedY,Obj *obj) {
  erase_obj(*obj);
  (*obj).ogX += addedX;
  (*obj).ogY += addedY;
  draw_obj(*obj);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GROUP funtions [TO CREATION AND UPDATES]:                                                                                     //
// Work with group of objs or sprites (good for multi tasking)                                                                   //
// [OBJ GROUPS || SPRITE GROUPS]                                                                                                 // 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////
// PART 1: SPRITES //
/////////////////////

void init_sprite_table(int originalSize) {
  sprite_table = (Sprite*) malloc(sizeof(Sprite) * (originalSize + 1));
  available_spr_i = (int*) malloc(sizeof(int) * (originalSize +1));
  spr_table_size = originalSize;
}

void extend_sprite_table(int newSize) {
  free(sprite_table);
  free(available_spr_i);
  sprite_table  = (Sprite*) malloc(sizeof(Sprite) * (newSize +1));
  available_spr_i = (int*) malloc(sizeof(int) * (newSize + 1));
  spr_table_size = newSize;
}

void insert_sprite_on_table(Sprite spr) {
  int i;
  int aux = spr_table_size;
  for (i = 0; i < spr_table_size; i++) {
    if (available_spr_i[i]) {
      sprite_table[i] = spr;
      available_spr_i[i] = 0;
      return;
    }
  }
  // i == spr_table_size? 
  //    it means we need more size on our table
  if (i == spr_table_size) {
    int newSize = spr_table_size + 10;
    Sprite* new_spr_table = (Sprite*) malloc(sizeof(Sprite) * (newSize + 1));
    for (i = 0; i < spr_table_size; i++) {
      new_spr_table[i] = sprite_table[i];
    }
    extend_sprite_table(newSize);
    for (int i = 0; i < aux; i++) {
      sprite_table[i] = new_spr_table[i];
      available_spr_i[i] = 0;
    }
    for (int i = aux; i < newSize; i++) {
      available_spr_i[i] = 1;
    }
    // try to insert again
    insert_sprite_on_table(spr);
  }
}

/////////////////////
//  PART 2: OBJS   //
/////////////////////

void init_obj_table(int originalSize) {
  obj_table = (Obj*) malloc(sizeof(Obj) * (originalSize + 1));
  available_obj_i = (int*) malloc(sizeof(int) * (originalSize +1));
  for (int i = 0; i < originalSize; i++) {
    available_obj_i[i] = 1;
  }
  obj_table_size = originalSize;
}

void extend_obj_table(int newSize) {
  free(obj_table);
  free(available_obj_i);
  obj_table  = (Obj*) malloc(sizeof(Obj) * (newSize +1));
  available_obj_i = (int*) malloc(sizeof(int) * (newSize + 1));
  obj_table_size = newSize;
}

void insert_obj_on_table(Obj obj) {
  int i;
  int aux = obj_table_size;
  for (i = 0; i < obj_table_size; i++) {
    if (available_obj_i[i]) {
      obj_table[i] = obj;
      available_obj_i[i] = 0;
      return;
    }
  }
  // i == spr_table_size? 
  //    it means we need more size on our table
  if (i == obj_table_size) {
    int newSize = obj_table_size + 10;
    Obj* new_obj_table = (Obj*) malloc(sizeof(Obj) * (newSize + 1));
    for (i = 0; i < obj_table_size; i++) {
      new_obj_table[i] = obj_table[i];
    }
    extend_obj_table(newSize);
    for (int i = 0; i < aux; i++) {
      obj_table[i] = new_obj_table[i];
      available_obj_i[i] = 0;
    }
    for (int i = aux; i < newSize; i++) {
      available_obj_i[i] = 1;
    }
    // try to insert again
    insert_obj_on_table(obj);
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GROUP funtions [TO CONTROL EVERY INSTANCE]:                                                                                   //
// Work with group of objs or sprites (good for multi tasking)                                                                   //
// [OBJ GROUPS || SPRITE GROUPS]                                                                                                 // 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* TESTING AREA */

void moveALL() {
  for (int i = 0; i < obj_table_size; i++) {
    if (!available_obj_i[i])
      move_obj(0, 1, &obj_table[i]);
  }
}

void Bubbling() {
  for (int i = 0; i < obj_table_size; i++) {
    if (!available_obj_i[i]) {
      move_obj(rand()%3-1, rand()%3-1, &obj_table[i]);
    }
  }
}

void TUNEL() { 
  for (int i = 0; i < obj_table_size; i++) {
    if (!available_obj_i[i]) {
      if (obj_table[i].ogX < screenW - 5 && obj_table[i].ogY < screenH - 5)
        move_obj(rand()%3,rand()%3,&obj_table[i]);
      else {
        if (obj_table[i].ogX >= screenW -5) 
          obj_table[i].ogX = 0;
        else {
          obj_table[i].ogY = 0;
        }
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN LOOP                                                                                                                     //
// Ready to use Cengine V2.0                                                                                                     //
// @Author: José Cutileiro                                                                                                       //
// Date: 27/12/2021 ===== XX/XX/XXXX                                                                                             //
//          ^                ^                                                                                                   //
//        start             end                                                                                                  //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
  init_frame();
  init_obj_table(10);
  init_sprite_table(10);
  Sprite sprTeste = init_sprite(TREE,TREE_W,TREE_H);
  for (int i = 0; i < 10000; i++) {
    Obj new = create_obj(sprTeste, rand()%screenW, rand()%(screenH)/2);
    //Obj new = create_obj(sprTeste, 2, 2);
    insert_obj_on_table(new);
  }
  //Obj objTeste = create_obj(sprTeste, 50, 50);
  //insert_obj_on_table(objTeste);
  while (key != EXIT) {
    key = buffer_delete();
    print_frame();
    usleep(DELAY*3);
    //draw_obj(objTeste);
    //move_obj(1, 0, objTeste);
    //moveALL();
    Bubbling();
    //TUNEL();
  }
}
