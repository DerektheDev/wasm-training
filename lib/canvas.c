#include <stdio.h>
#include <emscripten.h>

// init circle data and start render - JS
int main() {
  printf("Init circles\n");
  emscripten_run_script("render()");
}

// return circles to JS
int getCircles() {
  return 1;
}
