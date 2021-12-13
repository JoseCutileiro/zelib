#ifndef _CENGINE_
#define _CENGINE_

/* FRAME CONTROL            *
 * > Resolution:            *
 *      > 1366:768 (16:9)   *
 *                          */

#define screenH 104
#define screenW 674

/* Keyboard read input */

int kbhit(void);
char buffer_delete();


/* Sprite defenition */

typedef struct sprite{
  int size;
  int sqrt_size;
  char *info;
} Sprite,*SPRITES;

typedef struct obj{
  int x;
  int y;
  int objId;
  Sprite shape;
} Obj,*OBJ;




/* Frame display && Frame update */

void delay(int number_of_miliseconds);
void init_map(char map[screenH][screenW]);
void print_map(char map[screenH][screenW]);
void draw_shape(int x, int y, Sprite shape, char map[screenH][screenW]);
void erase_shape(int x, int y, Sprite shape, char map[screenH][screenW]);

/* Sprite update */
void move(int addedX, int addedY, Obj *obj, char map[screenH][screenW]);

#endif
