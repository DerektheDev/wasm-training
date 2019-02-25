#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>

// number of circles
#define NUM_CIRCLES 500

// circle struct
struct Circle {
  int x; // x coord
  int y; // y coord
  int r; // circle radius
  int cr; // color red
  int cg; // color green
  int cb; // color blue
};

// circle struct
struct CircleAnimationData {
  int x; // x coord
  int y; // y coord
  int r; // circle radius
  int xv; // x axis velocity
  int yv; // y axis velocity
  int xd; // x axis direction (1 = forward, 0 = backward)
  int yd; // y axis direction
};


// circles variable
struct Circle circles[NUM_CIRCLES];
struct CircleAnimationData animationData[NUM_CIRCLES];

// random number generator
int getRand(max) {
  return (rand() % max);
}

// init circle data and start render - JS
int main() {
  // seed random number generator
  srand(time(NULL));

  // create circles
  for (int i = 0; i < NUM_CIRCLES; i++) {
    int radius = getRand(50);

    // coords
    int x = getRand(1000) + radius;
    int y = getRand(1000) + radius;

    // fill animation data struct
    animationData[i].x = x;
    animationData[i].y = y;
    animationData[i].r = radius;
    animationData[i].xv = getRand(10);
    animationData[i].yv = getRand(10);
    animationData[i].xd = 1;
    animationData[i].yd = 1;

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

// return animated circles to JS
struct Circle * getCircles(int canvasWidth, int canvasHeight) {
  // yodate circle data
  for (int i = 0; i < NUM_CIRCLES; i++) {
    // collision right = set x direction backwards
    if((animationData[i].x + animationData[i].r) >= canvasWidth) animationData[i].xd = 0;
    // collision left
    if((animationData[i].x - animationData[i].r) <= 0) animationData[i].xd = 1;
    // collision top
    if((animationData[i].y - animationData[i].r) <= 0) animationData[i].yd = 1;
    // collision bottom
    if((animationData[i].y + animationData[i].r) >= canvasHeight) animationData[i].yd = 0;

    // move circle in specified direction
    if(animationData[i].xd == 1) {
      animationData[i].x += animationData[i].xv;
    } else {
      animationData[i].x -= animationData[i].xv;
    }

    if(animationData[i].yd == 1) {
      animationData[i].y += animationData[i].yv;
    } else {
      animationData[i].y -= animationData[i].yv;
    }

    // update matching circles
    circles[i].x = animationData[i].x;
    circles[i].y = animationData[i].y;
  }

  return circles;
}
