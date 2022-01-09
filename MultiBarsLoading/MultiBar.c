#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <threads.h>
#include <unistd.h>

#define NUMBER_OF_BARS 20
#define BAR_LENGTH 50

typedef struct {
  int value;
  int finalValue;
} Bar;

Bar bars[NUMBER_OF_BARS];

int drawBar(int index) {
  int value = bars[index].value;
  int i;
  int finalValue = bars[index].finalValue;
  int toDraw = (value * BAR_LENGTH) / finalValue;
  if (toDraw > BAR_LENGTH) {
    toDraw = BAR_LENGTH; 
  }
  printf("[");
  for (i = 0; i < toDraw; i++) {
    printf("#");
  }
  for (;i < BAR_LENGTH; i++) {
    printf(" ");
  }
  printf("]\n");
  return toDraw;
}

void* threadFunc(int value) {
 
  int index = value;
  while (1) {
    bars[value].value+=1;
    usleep(rand()%1000);
  }
  return NULL;
}

int main() {
  int ok = 0;
  pthread_t threads[NUMBER_OF_BARS];
  for (int i = 0; i < NUMBER_OF_BARS; i++) {
    bars[i].value = 0;
    bars[i].finalValue = rand()%10000;
  }
  for (int i = 0; i < NUMBER_OF_BARS; i++) {
   
    pthread_create(&threads[i],NULL,threadFunc,i);
  }
  while (!ok) {
    ok = 1;
    for (int i = 0; i < NUMBER_OF_BARS; i++) {
      drawBar(i);
      if (bars[i].value < bars[i].finalValue) {
        ok = 0;
      }
    }
    
    if (!ok) {
      printf("\033[%dF",NUMBER_OF_BARS);
    }
    usleep(100);
  }
  printf("\nOK\n");
  return 0;
}
