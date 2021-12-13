/* Author: José Cutileiro                      * 
 * here you can edit all memory acess directly */

#ifndef _MEMORY_
#define _MEMORY_

#include "Cengine.h"
#include "frame.h"

/* ------------ DEFAULT SPRITE PACK --------------------*/

void cube(SPRITES memory,int index);

/*------------------------------------------------------*/

void addObj(OBJ memory,Sprite shape,int *numberOfObjs,int x,int y);
SPRITES init_memory_sprites();
OBJ init_memory_obj();


#endif
