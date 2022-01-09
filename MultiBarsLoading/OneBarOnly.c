#include <stdlib.h>
#include <stdio.h>
#include <threads.h>
#include <unistd.h>

#define NUMBER_OF_BARS 1  // This version only works for one bar
#define BAR_LENGTH 30

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
  printf("\r[");
  for (i = 0; i < toDraw; i++) {
    printf("-");
  }
  for (;i < BAR_LENGTH; i++) {
    printf(" ");
  }
  printf("]");
  return 0;
}

int main() {
  int ok = 0;
  for (int i = 0; i < NUMBER_OF_BARS; i++) {
    bars[i].value = 0;
    bars[i].finalValue = rand() % 100000;
  }
  while (!ok) {
    ok = 1;
    bars[0].value++;
    drawBar(0);
    if (bars[0].value != bars[0].finalValue) {
      ok = 0;
    }
    usleep(100);
  }
  printf("\nOK\n");
  return 0;
}
