#include "Cengine.h"
#include "frame.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Delay the frame rate
void delay(int number_of_miliseconds)
{
    // Converting time into milli_seconds
    int milli_seconds = number_of_miliseconds;
  
    // Storing start time
    clock_t start_time = clock();
    
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

// Clean frame
void init_map(char map[screenH][screenW]){
  int i,j;
  for (i=0;i<screenH;i++){
    for (j=0;j<screenW;j++){
      if (j==0 || j== screenW-2){
        map[i][j] = WALL;
      }
      if (i==0 || i == screenH-2){
        map[i][j] = WALL;
      }
      if (j== screenW-1){
        map[i][j] = '\0';
      }
      if (j>0 && j<screenW-2 && i>0 && i<screenH-2){
        map[i][j] = VOID;
      }
    }
  }
}

// Print a frame
void print_map(char map[screenH][screenW]){
  int i;
  for (i=0;i<screenH;i++){
    if (i!= screenH-2)
      printf("%s\n",map[i]);
    else
      printf("%s",map[i]);
  }
}

// Sprites general behaviour

void draw_shape(int x,int y, Sprite shape,char map[screenH][screenW]){
  int i,j,k=0;
  for (i=0;i<shape.sqrt_size;i++){
    for (j=0;j<shape.sqrt_size;j++){
      if (x+j >= screenW-2 || y+i >= screenH-2 || x+j < 2 || y+i < 2){
        continue;
      }

      if (shape.info[k] != NULLINFO){
        map[y+i][x+j] = shape.info[k];
      }
      k++;
    }
  }
}

void erase_shape(int x,int y, Sprite shape,char map[screenH][screenW]){
  int i,j,k=0;
  for (i=0;i<shape.sqrt_size;i++){
    for (j=0;j<shape.sqrt_size;j++){
      if (x+j >= screenW-2 || y+i >= screenH-2 || x+j < 2 || y+i < 2){
        continue;
      }
      if (shape.info[k] != NULLINFO){
        map[y+i][x+j] = VOID;
      }
      k++;
    }
  }
}

