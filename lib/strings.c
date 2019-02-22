#include <emscripten.h>
#include <stdio.h>

char * str = "my string variable";

char * getStr() {
  return str;
}

int getNumber() {
  int num = 22;
  // emscripten_debugger();
  if (num < 30) {
    emscripten_log(EM_LOG_WARN, "'num' less than 30");
  }
  return num;
}

int main() {
  printf("WASM Ready\n");
  return 1;
}
