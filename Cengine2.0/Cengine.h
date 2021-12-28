#ifndef _ACE_ 
#define _ACE_

/* GLOBAL CONSTS */

// GENERAL

#define DELAY 10000     // Microseconds
#define EXIT '_'        //EXIT BUTTON
#define screenW 650     // Screen witdh
#define screenH 100      // Screen Heigth

// FRAME

#define VOID ','
#define PIXEL '#'
#define SPACE ' '
#define ENDLINE '\0'
#define NEXTLINE '\n'

// STRUCTS

typedef struct sprite{
  char* info;
  int wid;
  int hei;

}Sprite,SPRITES;

typedef struct obj{
  Sprite sprite;
  int ogX;
  int ogY;
}Obj,*OBJS;

/* KEYBOARD */

int kbhit(void);
char buffer_delete();



#endif
