#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>

// number of circles
#define NUM_CIRCLES 20

// circle struct
struct Circle {
  int x; // x coord
  int y; // y coord
  int r; // circle radius
  int cr; // color red
  int cg; // color green
  int cb; // color blue
};

// circles variable
struct Circle circles[NUM_CIRCLES];

// random number generator
int getRand(max) {
  return (rand() % max);
}

// init circle data and start render - JS
int main() {
  // seed random number generator
  srand(time(NULL));

  printf("Init circles\n");
  // create circles
  for (int i = 0; i < NUM_CIRCLES; i++) {
    int radius = getRand(50);

    // coords
    int x = getRand(1000) + radius;
    int y = getRand(1000) + radius;

    // fill circle struct
    circles[i].x = x;
    circles[i].y = y;
    circles[i].r = radius;
    circles[i].cr = getRand(255);
    circles[i].cg = getRand(255);
    circles[i].cb = getRand(255);
  }

  // start JS rendering
  EM_ASM({render($0, $1);}, NUM_CIRCLES * 6, 6);
}

// return circles to JS
struct Circle * getCircles() {
  return circles;
}
